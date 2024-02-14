#include "Thread.h"

Thread::Thread() : appInstance(nullptr), isRunning(false) 
{
}

Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

void Thread::Init(App* instance) {
    appInstance = instance;
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

DWORD WINAPI Thread::ThreadProc(void* param)
{
    Thread* pThread = (Thread*)param;

    pThread->OnThread();
    return;
}
void Thread::Join() {
    if (isRunning) {
        WaitForSingleObject(threadHandle, INFINITE);
        Exit();
    }
}

void Thread::Exit() {
    if (isRunning) {
        CloseHandle(threadHandle);
        isRunning = false;
    }
}


