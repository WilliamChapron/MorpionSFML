// App.cpp
#include "App.h"

// Initialisation de l'instance statique à nullptr
App* App::instance = nullptr;

App::App() : pServer(nullptr), myMorpion(nullptr), turnCounter(0), player1(nullptr), player2(nullptr), playerNumber(0), pCout(nullptr) {
}

App::~App() {
    delete pServer;
    delete myMorpion;
    delete player1;
    delete player2;

    fclose(pCout);
    FreeConsole();
}

App* App::GetInstance() {
    // Crée l'instance si elle n'existe pas déjà
    if (instance == nullptr) {
        instance = new App();
    }

    return instance;
}

void App::Init(HINSTANCE hInstance) {
    AllocConsole(); // Créer une nouvelle console
    freopen_s(&pCout, "CONOUT$", "w", stdout);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ServerWindowClass";

    RegisterClass(&wc);

    hwnd = new CreateWindowExW(
        0,
        L"ServerWindowClass",
        L"Server App",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        0,
        0,
        hInstance,
        0);

    if (!hwnd) return;

    hwnd = &hwnd;

    ShowWindow(&hwnd, SW_HIDE);

    // Initialiser et démarrer le serveur
    pServer = new ServerSocket(80);
    if (!pServer->StartAsyncListening(hwnd)) {
        return;
    }

    myMorpion = new Morpion();
}

void App::Run() {
    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }
}
