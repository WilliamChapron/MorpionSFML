

#include "Morpion.h"

#include "App.h"

#include "Includes.h"
#include "ServerSocket.h"
#include "Defines.h"
#include "Morpion.h"

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

    // Initialise le singleton avec l'instance de l'application
    //OutputDebugStringA("------------------------------------------------------------------point dentree------------------------------------------------------------------");
    myApp->Init(hInstance);

    // Exécute l'application
    myApp->Run();

    // Libère la mémoire utilisée par le singleton (facultatif, car l'OS libérera la mémoire à la fin du programme)
    delete myApp;

    return 0;
}




// #TODO Send Failed to client with send
// #TODO Handle when client disconnected
// #TODO Handle Broadcast to all clients
// #NOW bidirectional request, request and response + connection timed out working