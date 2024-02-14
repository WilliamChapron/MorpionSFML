#include "Thread.h"
#include "Defines.h"

Thread::Thread() : appInstance(nullptr), isRunning(false) 
{
}

Thread::~Thread() {
}

DWORD WINAPI Thread::ThreadProc(void* param)
{
    Thread* pThread = (Thread*)param;

    pThread->OnThread();
    return 0;
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        thread = CreateThread(NULL, 0, ThreadProc, this, NULL, NULL);
    }
}

void Thread::OnThread()
{

}

void Thread::Exit() {
    if (isRunning) {
        CloseHandle(thread);
        isRunning = false;
    }
}


