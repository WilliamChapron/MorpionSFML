#include "Thread.h"

Thread::Thread() : isRunning(false) {}

Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

void Thread::Start(void (*function)()) {
    if (!isRunning) {
        threadParams = reinterpret_cast<LPARAM>(function);  // Stocker la fonction dans LPARAM
        this->appInstance = appInstance;
        isRunning = true;
        threadHandle = CreateThread(NULL, 0, ThreadFuncWrapper, this, 0, NULL);
    }
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

DWORD WINAPI Thread::ThreadFuncWrapper(LPVOID param) {
    Thread* pThread = static_cast<Thread*>(param);
    if (pThread) {
        void (*function)(App*) = reinterpret_cast<void (*)(App*)>(pThread->threadParams);
        App* appInstance = pThread->appInstance;
        (function)(appInstance);
    }
    return 0;
}
