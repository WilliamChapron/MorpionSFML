#include "SThread.h"

Thread::Thread(std::function<void()> function)
    : threadFunction(function), isRunning(false) {}

// detruit quand fini
Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

/*DWORD est le type de données représentant un entier non signé 
de 32 bits, et WINAPI est une macro qui définit la convention 
d'appel utilisée par la fonction  LPVOID (longueur de pointeur non signée), 
qui est généralement utilisé pour passer des données arbitraires à la fonction*/
DWORD WINAPI Thread::ThreadFuncWrapper(LPVOID param) {
    Thread* pThread = static_cast<Thread*>(param)/*efffectue une conversion de type*/;
    if (pThread) /*vérifie si non nul*/ {
        pThread->threadFunction()/*appelle la methode threadFunction*/;
    }
    return 0;
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        threadHandle = CreateThread(NULL/*indique que les attributs de sécurité par défaut seront utilisés*/,
            0/*signifie que la pile par défaut sera utilisée*/, 
            ThreadFuncWrapper/*pointeur vers la fonction qui sera exécutée par le thread*/, 
            this/*pointeur vers l'objet Thread*/,
            0/*indique que le thread commencera immédiatement son exécution*/,
            NULL/* indique que l'identifiant du thread n'est pas nécessaire*/);
    }
}

void Thread::Join() {
    if (isRunning) {
        WaitForSingleObject(threadHandle/*poignée du thread que nous voulons attendre*/, 
            INFINITE/* attendra indéfiniment jusqu'à ce que l'objet (threadHandle) atteigne l'état signalé*/);
        Exit();
    }
}

void Thread::Exit() {
    if (isRunning) {
        CloseHandle(threadHandle);
        isRunning = false;
    }
}