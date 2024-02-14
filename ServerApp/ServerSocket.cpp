// ServerSocket.cpp
#include "ServerSocket.h"
#include "App.h"
#include "JSON.h"
#include "Player.h"
#include "Threads.h"


static ServerSocket* currentInstance = nullptr;

LRESULT CALLBACK ServerSocket::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    App* myApp = App::GetInstance();
    ServerSocket* currentInstance = reinterpret_cast<ServerSocket*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    ThreadListen myThreadListen;
    ThreadClients myThreadClients;

    switch (uMsg) {
    case WM_LISTEN_SOCKET:
    {
        PRINT("HEy");

        myThreadListen.Init(currentInstance, myApp, currentInstance);
        myThreadListen.Start();

    }
    case WM_CLIENTS_SOCKET:
    {
        PRINT("HEy2");

        myThreadClients.Init(currentInstance, myApp, wParam);
        myThreadClients.Start();

        break; 
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    // Wait Thread finish before exit
    WaitForSingleObject(myThreadListen.thread, INFINITE);
    WaitForSingleObject(myThreadClients.thread, INFINITE);
    myThreadListen.Exit();
    myThreadClients.Exit();


    return 0;
}

void ServerSocket::HandleListenSocket(App* myApp, ServerSocket* currentInstance) {
    SOCKET newClientSocket = accept(myApp->GetServerSocket()->listenSocket, nullptr, nullptr);
    if (newClientSocket == INVALID_SOCKET) {
        return;
    }

    if (myApp->GetPlayer1() == nullptr || myApp->GetPlayer2() == nullptr) {
        SetPlayers(myApp);
        std::cout << "Nouvelle connexion établie." << std::endl;
        currentInstance->AddClientSocket(newClientSocket);
    }

}

void ServerSocket::HandleClientsSocket(App* myApp, WPARAM wParam) {
    SOCKET clientSocket = static_cast<SOCKET>(wParam);
    json receivedJson = ReceiveJsonFromSocket(clientSocket);

    if (!receivedJson.empty()) {
        sf::Vector2i mousePosition = {
            std::stoi(receivedJson["x"].get<std::string>()),
            std::stoi(receivedJson["y"].get<std::string>())
        };

        int index = myApp->GetTurnCounter() % 2;
        myApp->turn(mousePosition, index, clientSocket);

        if (myApp->GetMorpion()->checkEnd(Symbol::X) || myApp->GetMorpion()->checkEnd(Symbol::O)) {
            Symbol winningPlayer = myApp->GetMorpion()->currentPlayer->symbol;
            json resultMessage;

            if (winningPlayer == Symbol::X) {
                resultMessage = CreateJsonMessage("end", "O");
            }
            else if (winningPlayer == Symbol::O) {
                resultMessage = CreateJsonMessage("end", "X");
            }
            else {
                resultMessage = CreateJsonMessage("end", "equal");
            }
            myApp->GetServerSocket()->BroadcastMessage(resultMessage);
        }
    }
}

void ServerSocket::SetPlayers(App* myApp) {
    if (myApp->GetPlayer1() == nullptr && myApp->GetPlayer2() == nullptr) {
        myApp->SetPlayer1(new Player("Player1", Symbol::X, 0));
        myApp->GetMorpion()->currentPlayer = myApp->GetPlayer1();
    }
    else if (myApp->GetPlayer1() != nullptr && myApp->GetPlayer2() == nullptr) {
        myApp->SetPlayer2(new Player("Player2", Symbol::O, 0));
    }
}

ServerSocket::ServerSocket(int port, HINSTANCE hInstance) : port(port), listenSocket(INVALID_SOCKET){


    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = ServerSocket::WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "MyWindowClass";

    if (!RegisterClassEx(&wc)) {
    }

    hwnd = CreateWindowEx(0, "MyWindowClass", "My Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, GetModuleHandle(0), nullptr);

    //if (!hwnd) {
    //}

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    ShowWindow(hwnd, SW_HIDE);
}

ServerSocket::~ServerSocket() {
    for (SOCKET clientSocket : clientSockets) {
        closesocket(clientSocket);
    }
    WSACleanup();
    currentInstance = nullptr;
}

bool ServerSocket::StartAsyncListening() {
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
void ServerSocket::AddClientSocket(SOCKET clientSocket) {
    clientSockets.push_back(clientSocket);

    if (WSAAsyncSelect(clientSocket, hwnd, WM_CLIENTS_SOCKET, FD_READ | FD_CLOSE) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::cout << "Failed to start asynchronous listening for client socket. Error code: " << errorCode << std::endl;
    }
}

void ServerSocket::BroadcastMessage(const json& jsonData) {
    std::string jsonString = jsonData.dump(); // Json to string with nlohmann

    for (SOCKET clientSocket : clientSockets) {
        send(clientSocket, jsonString.c_str(), jsonString.size(), 0);
    }
}

bool ServerSocket::isSocketAtIndex(SOCKET socketToCheck, int indexToCheck) {
    auto it = std::find(clientSockets.begin(), clientSockets.end(), socketToCheck);

    if (it != clientSockets.end() && std::distance(clientSockets.begin(), it) == indexToCheck) {
        return true;
    }
    else {
        return false;
    }
}

void ServerSocket::Close() {
    closesocket(listenSocket);
}