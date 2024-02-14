#include "Threads.h"
#include "App.h"
#include "Defines.h"
#include "ServerSocket.h"

ThreadClients::ThreadClients() : Thread()
{
}

void ThreadClients::Init(ServerSocket* instance, App* myApp, WPARAM wParam) {
    instanceFunc = instance;
    args.myApp = myApp;
    args.wParam = wParam;
}

void ThreadClients::OnThread() {
    //App* myApp = App::GetInstance();
    /*while (true) {
        myApp->RunServerWeb();
    }*/
    instanceFunc->HandleClientsSocket(args.myApp, args.wParam);
    PRINT("THREAD CLIENTS");
}

ThreadListen::ThreadListen() : Thread()
{
}


void ThreadListen::Init(ServerSocket* instance, App* myApp, ServerSocket* currentInstance) {
    instanceFunc = instance;
    args.myApp = myApp;
    args.currentInstance = currentInstance;
}

void ThreadListen::OnThread() {
    /*App* myApp = App::GetInstance();
    while (true) {
        myApp->RunServerSocket();
    }*/
    instanceFunc->HandleListenSocket(args.myApp, args.currentInstance);

    PRINT("THREAD LISTEN");

}
