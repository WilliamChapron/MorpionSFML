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
    LPARAM threadParams;  // Utiliser LPARAM pour stocker les paramètres nécessaires
    App* appInstance;
    bool isRunning;
    static DWORD WINAPI ThreadFuncWrapper(LPVOID param);

    // Ajoutez ces méthodes si nécessaire
    void Join();
    void Exit();
};
