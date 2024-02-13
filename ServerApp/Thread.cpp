#include "Thread.h"

Thread::Thread(std::function<void()> function)
    : threadFunction(function), isRunning(false) {}

// detruit quand fini
Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}


DWORD WINAPI Thread::ThreadFuncWrapper(LPVOID param) {
    Thread* pThread = static_cast<Thread*>(param)/*efffectue une conversion de type*/;
    if (pThread) /*vérifie si non nul*/ {
        pThread->threadFunction()/*appelle la methode threadFunction*/;
    }
    return 0;
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        threadHandle = CreateThread(NULL, 0, ThreadFuncWrapper, this, 0, NULL);
    }
}

void Thread::Join(HANDLE threadHandle) {
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