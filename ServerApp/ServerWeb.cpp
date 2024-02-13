// ServerWeb.cpp
#include "ServerWeb.h"
#include "App.h"
#include "JSON.h"
#include "Player.h"


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
            SOCKET newClientSocket = accept(myApp->pServer->listenSocket, nullptr, nullptr);
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

        json receivedJson = ReceiveJsonFromSocket(clientSocket);



        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

ServerWeb::ServerWeb(int port, HINSTANCE hInstance) : port(port), listenSocket(INVALID_SOCKET) {

    AllocConsole(); // Créer une nouvelle console
    FILE* pCout;
    freopen_s(&pCout, "CONOUT$", "w", stdout);


    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = ServerWeb::WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "MyWindowClass";

    if (!RegisterClassEx(&wc)) {
    }

    hwnd = CreateWindowEx(0, "MyWindowClass", "My Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, GetModuleHandle(0), nullptr);

    if (!hwnd) {
    }

    // La fenêtre a été créée avec succès
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

void ServerWeb::BroadcastMessage(const json& jsonData) {
    std::string jsonString = jsonData.dump(); // Json to string with nlohmann

    for (SOCKET clientSocket : clientSockets) {
        send(clientSocket, jsonString.c_str(), jsonString.size(), 0);
    }
}

void ServerWeb::Close() {
    closesocket(listenSocket);
}