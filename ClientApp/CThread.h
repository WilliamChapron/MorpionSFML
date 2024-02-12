#pragma once

#include <thread>
#include <functional>

class Thread
{
public:

    Thread(std::function<void()> threadFunction);
    ~Thread();

    void Start();
    void Join();

private:
    std::thread thread;
    std::function<void()> threadFunction;
    bool isRunning;
};

