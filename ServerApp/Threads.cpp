
#include "Threads.h"
#include "App.h"
#include "Defines.h"

ThreadWeb::ThreadWeb() : Thread() 
{
}

void ThreadWeb::OnThread() {
    App* myApp = App::GetInstance();
    while (true) {
        myApp->RunServerWeb();
    }
    //PRINT(myApp->pServer);
    //while (true) {
    //    
    //}

    //while (true) {
    //    PRINT("THREAD WEB");
    //}

}

ThreadSocket::ThreadSocket() : Thread() 
{
}

void ThreadSocket::OnThread() {
    App* myApp = App::GetInstance();

    //PRINT(myApp);
    //while (true) {
    //    PRINT("THREAD SOCKET ");
    //}
    //PRINT(myApp->GetServerSocket());

        //PRINT(myApp->pServer);
    //for (int i = 0; i < 1000; ++i) {
    //    myApp->RunServerSocket();
    //}
    while (true) {
        myApp->RunServerSocket();
    }


}
