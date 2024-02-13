#pragma once
#include <windows.h>
#include <functional>

class Thread
{
public:

    Thread(std::function<void()> threadFunction);
    ~Thread();

    void Start();
    void Join();

private:
    HANDLE threadHandle;
    std::function<void()> threadFunction;
    bool isRunning;
    static DWORD WINAPI ThreadFuncWrapper(LPVOID param);
};

