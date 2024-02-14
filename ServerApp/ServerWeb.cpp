#include "ServerWeb.h"
#include "App.h"
#include "JSON.h"
#include "Player.h"
#include "Morpion.h"


std::vector<WebLog> webLogs;

// Fonction pour enregistrer une action dans les journaux
void LogAction(const std::string& action, const std::string& player, const std::string& symbol) 
{
    std::time_t now = std::time(nullptr);
    struct tm timeinfo;
    char timeBuffer[100];
    localtime_s(&timeinfo, &now);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);


    WebLog log;
    log.action = action;
    log.player = player;
    log.symbol = symbol;
    log.time = timeBuffer;

    webLogs.push_back(log);
}

// Fonction pour d�finir un joueur
void SetPlayer(const std::string& playerName) 
{
    LogAction("Set player", playerName, "");
}

// Fonction pour placer un symbole
void PlaceSymbol(const std::string& playerName, const std::string& symbol, const std::string& position) 
{
    LogAction("Place symbol", playerName, symbol + " at " + position);
}


static ServerWeb* currentInstance = nullptr;

LRESULT CALLBACK ServerWeb::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    App* myApp = App::GetInstance();
    PRINT("CallBack");
    ServerWeb* currentInstance = reinterpret_cast<ServerWeb*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg) {
    case WM_LISTEN_SOCKET:
    {
        PRINT("LISTEN SOCKET");
        while (true) {
            SOCKET newClientSocket = accept(currentInstance->listenSocket, nullptr, nullptr);
            if (newClientSocket == INVALID_SOCKET) {
                break;
            }
            currentInstance->AddClientSocket(newClientSocket);
        }
        break;
    }
    case WM_CLIENTS_SOCKET:
    {

        PRINT("EVENT CLIENTS");
        SOCKET clientSocket = static_cast<SOCKET>(wParam);
        currentInstance->ResponseRequest(clientSocket);

        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

ServerWeb::ServerWeb(int port, HINSTANCE hInstance) : port(port), pCout(nullptr), listenSocket(INVALID_SOCKET) {

    //AllocConsole(); // Cr�er une nouvelle console
    //freopen_s(&pCout, "CONOUT$", "w", stdout);


    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = ServerWeb::WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "MyWindowClassWeb";

    if (!RegisterClassEx(&wc)) {
    }

    hwnd = CreateWindowEx(0, "MyWindowClassWeb", "My Window Web", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, GetModuleHandle(0), nullptr);

    if (!hwnd) {
    }

    // La fen�tre a �t� cr��e avec succ�s
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    ShowWindow(hwnd, SW_HIDE);


}

ServerWeb::~ServerWeb() {
    for (SOCKET clientSocket : clientSockets) {
        closesocket(clientSocket);
    }
    WSACleanup();
    fclose(pCout);
    FreeConsole();
    currentInstance = nullptr;
}

bool ServerWeb::StartAsyncListening() {
    PRINT("StartAsyncListening");


    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return false;
    }


    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) != 1) {
        std::cerr << "Failed to convert IP address." << std::endl;
        Close();
        return false;
    }

    serverAddress.sin_port = htons(port);

    if (bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        Close();
        return false;
    }

    if (WSAAsyncSelect(listenSocket, hwnd, WM_LISTEN_SOCKET, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR) {
        std::cerr << "Failed to start asynchronous listening." << std::endl;
        Close();
        return false;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for incoming connections." << std::endl;
        Close();
        return false;
    }


    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for incoming connections." << std::endl;
        closesocket(listenSocket);
        return false;
    }

    return true;
}
void ServerWeb::AddClientSocket(SOCKET clientSocket) {
    clientSockets.push_back(clientSocket);

    if (WSAAsyncSelect(clientSocket, hwnd, WM_CLIENTS_SOCKET, FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::cout << "Failed to start asynchronous listening for client socket. Error code: " << errorCode << std::endl;
    }
}






std::string GenerateHtmlContent() {
    App* myApp = App::GetInstance();

    std::string htmlContent = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Morpion</title>
    <style>
        .cross {
            color: red;
        }

        .circle {
            color: blue;
        }

        .log {
            float: right;
            margin-right: 20px;
            width: 200px;
            border: 1px solid black;
            padding: 10px;
        }
    </style>
</head>
<body>
    <h1>Morpion</h1>

    <!-- Tableau pour afficher le morpion -->
    <table border='1' cellpadding='10'>
    <tr>
)";

    // Remplir le tableau avec les symboles
    for (int i = 0; i < 8; ++i) {
        // Ajouter une nouvelle ligne � chaque troisi�me �l�ment
        if (i % 3 == 0 && i != 0) {
            htmlContent += "</tr><tr>";
        }

        htmlContent += "<td>";
        // Ajouter la classe CSS en fonction du symbole
        if (myApp->myMorpion->board[i] == Symbol::X) {
            htmlContent += "<div class='cross'>X</div>";
        }
        else if (myApp->myMorpion->board[i] == Symbol::O) {
            htmlContent += "<div class='circle'>O</div>";
        }
        else {
            htmlContent += "<div>Empty</div>";
        }
        htmlContent += "</td>";
    }

    htmlContent += "</tr></table>";

    // Ajouter la section de journal des actions
    htmlContent += R"(
    <div class="log">
        <h2>Logs</h2>
        <ul>
    )";

    // Ajouter chaque entr�e de journal comme un �l�ment de liste
    for (const auto& log : webLogs) {
        htmlContent += "<li>" + log.time + " - " + log.action + " by " + log.player + " (" + log.symbol + ")</li>";
    }

    htmlContent += R"(
        </ul>
    </div>
    )";

    // Fin du contenu HTML
    htmlContent += R"(
</body>
</html>
)";

    return htmlContent;
}


void ServerWeb::ResponseRequest(SOCKET clientSocket) {



    std::string htmlContent = GenerateHtmlContent();


    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "Content-Length: " + std::to_string(htmlContent.size()) + "\r\n";
    httpResponse += "\r\n";


    send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);


    send(clientSocket, htmlContent.c_str(), htmlContent.size(), 0);
}


void ServerWeb::Close() {
    closesocket(listenSocket);
}