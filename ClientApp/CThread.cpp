#include "CThread.h"

Thread::Thread(std::function<void()> function)
    : threadFunction(function), isRunning(false) {}

Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

DWORD WINAPI Thread::ThreadFuncWrapper(LPVOID param) {
    Thread* pThread = static_cast<Thread*>(param);
    if (pThread) {
        pThread->threadFunction();
    }
    return 0;
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        threadHandle = CreateThread(NULL, 0, ThreadFuncWrapper, this, 0, NULL);
    }
}

void Thread::Join() {
    if (isRunning) {
        WaitForSingleObject(threadHandle, INFINITE);
        CloseHandle(threadHandle);
        isRunning = false;
    }
}