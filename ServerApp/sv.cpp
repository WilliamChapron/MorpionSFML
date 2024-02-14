

#include "Morpion.h"
#include "App.h"
#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"
#include "Morpion.h"
#include "Thread.h"
#include "Threads.h"

#include "Time.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>


//#include <nlohmann/json.hpp>
//using json = nlohmann::json;
//#include "JSON.h";




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    App* myApp = App::GetInstance();
    myApp->Init(hInstance);

    //while (true) {
    //    myApp->RunServerSocket();
    //    myApp->RunServerWeb();
    //}

    //App::RunServerWeb(myApp->pServerWeb);



    ThreadSocket thread1(myApp);
    ThreadWeb thread2(myApp);
    PRINT(myApp->pServer);
    PRINT(myApp->pServerWeb);
    thread1.Start(App* instance);
    thread2.Start(&App::RunServerWeb);

    delete myApp;

    return 0;
}



// #TODO Send Failed to client with send
// #TODO Handle when client disconnected
// #TODO Handle Broadcast to all clients
// #NOW bidirectional request, request and response + connection timed out working