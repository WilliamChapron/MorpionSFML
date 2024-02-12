#include "CThread.h"

Thread::Thread(std::function<void()> function)
    : threadFunction(function), isRunning(false) {}

Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        thread = std::thread(threadFunction);
    }
}

void Thread::Join() {
    if (isRunning) {
        thread.join();
        isRunning = false;
    }
}