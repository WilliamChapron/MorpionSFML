
#include "Threads.h"

#include "App.h"

ThreadWeb::ThreadWeb() : Thread() 
{
}

void ThreadWeb::OnThread() {
    appInstance->
}

ThreadSocket::ThreadSocket() : Thread() 
{
}

void ThreadSocket::OnThread() {
    appInstance->RunServerSocket();
}
