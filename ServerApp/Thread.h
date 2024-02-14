#pragma once
#include "Includes.h"

class App;

class Thread {
public:
    Thread();
    ~Thread();

    void Init(App* instance);
    void Start();


    
protected:
    HANDLE thread;
    App* appInstance;
    virtual void OnThread();
private:

    static DWORD WINAPI ThreadProc(void* param);



    bool isRunning;

    // Ajoutez ces m�thodes si n�cessaire
    void Join();
    void Exit();
};
