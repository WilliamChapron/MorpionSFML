#pragma once
#include "Thread.h"

class ThreadWeb : public Thread {
public:
    ThreadWeb();
    void OnThread() override;
};

class ThreadSocket : public Thread {
public:
    ThreadSocket();
    void OnThread() override;
};
