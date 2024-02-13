#pragma once
#include "Includes.h"
#include <functional>

class Thread
{
public:

    Thread(std::function<void()> threadFunction);
    ~Thread();// fonction Delete 

    void Start();
    void Join(HANDLE threadHandle);
    void Exit();

private:
    HANDLE threadHandle;
    std::function<void()> threadFunction;
    bool isRunning;
    static DWORD WINAPI ThreadFuncWrapper(LPVOID param);
};
