#pragma once
#include "Includes.h"

class App;

class Thread {
public:
    Thread();
    ~Thread();

    void Start(void (*function)());

private:
    HANDLE threadHandle;
    LPARAM threadParams;  // Utiliser LPARAM pour stocker les param�tres n�cessaires
    App* appInstance;
    bool isRunning;
    static DWORD WINAPI ThreadFuncWrapper(LPVOID param);

    // Ajoutez ces m�thodes si n�cessaire
    void Join();
    void Exit();
};
