#pragma once
#include <windows.h>
#include <functional>

class Thread
{
public:

    Thread(std::function<void()> threadFunction);
    ~Thread();// fonction Delete 

    void Start();
    void Join();
    void Exit();

private:
    HANDLE threadHandle;
    std::function<void()> threadFunction;
    bool isRunning;
    static DWORD WINAPI ThreadFuncWrapper(LPVOID param);
};

