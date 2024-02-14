// Threads.h

#pragma once

#include "Includes.h"
#include "Thread.h"

class App;
class ServerSocket;

struct ThreadClientsArgs {
    App* myApp;
    WPARAM wParam;
};

class ThreadClients : public Thread {
public:
    ThreadClients();
    void OnThread() override;
    void Init(ServerSocket* instance, App* myApp, WPARAM wParam);

private:
    ServerSocket* instanceFunc;
    ThreadClientsArgs args;
};


struct ThreadListenArgs {
    App* myApp;
    ServerSocket* currentInstance;
};

class ThreadListen : public Thread {
public:
    ThreadListen();
    void OnThread() override;
    void Init(ServerSocket* instance, App* myApp, ServerSocket* currentInstance);

private:
    ServerSocket* instanceFunc;
    ThreadListenArgs args;
};
