#pragma once
#include "Includes.h"

class App;

class Thread {
public:
    Thread();
    ~Thread();

    void Init(App* instance);
    void Start();

    virtual void OnThread();
    

private:

    static DWORD WINAPI ThreadProc(void* param);

    HANDLE thread;
    App* appInstance;

    bool isRunning;

    // Ajoutez ces m�thodes si n�cessaire
    void Join();
    void Exit();
};
