#pragma once
#include "Includes.h"

class App;

class Thread {
public:
    Thread();
    ~Thread();


    void Start();
    void Exit();

    virtual void OnThread();

    HANDLE thread;
    
protected:

    App* appInstance;

private:

    static DWORD WINAPI ThreadProc(void* param);



    bool isRunning;


};
