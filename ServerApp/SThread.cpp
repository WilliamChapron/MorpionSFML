#include "SThread.h"

Thread::Thread(std::function<void()> function)
    : threadFunction(function), isRunning(false) {}

// detruit quand fini
Thread::~Thread() {
    if (isRunning) {
        Join();
    }
}

/*DWORD est le type de donn�es repr�sentant un entier non sign� 
de 32 bits, et WINAPI est une macro qui d�finit la convention 
d'appel utilis�e par la fonction  LPVOID (longueur de pointeur non sign�e), 
qui est g�n�ralement utilis� pour passer des donn�es arbitraires � la fonction*/
DWORD WINAPI Thread::ThreadFuncWrapper(LPVOID param) {
    Thread* pThread = static_cast<Thread*>(param)/*efffectue une conversion de type*/;
    if (pThread) /*v�rifie si non nul*/ {
        pThread->threadFunction()/*appelle la methode threadFunction*/;
    }
    return 0;
}

void Thread::Start() {
    if (!isRunning) {
        isRunning = true;
        threadHandle = CreateThread(NULL/*indique que les attributs de s�curit� par d�faut seront utilis�s*/,
            0/*signifie que la pile par d�faut sera utilis�e*/, 
            ThreadFuncWrapper/*pointeur vers la fonction qui sera ex�cut�e par le thread*/, 
            this/*pointeur vers l'objet Thread*/,
            0/*indique que le thread commencera imm�diatement son ex�cution*/,
            NULL/* indique que l'identifiant du thread n'est pas n�cessaire*/);
    }
}

void Thread::Join() {
    if (isRunning) {
        WaitForSingleObject(threadHandle/*poign�e du thread que nous voulons attendre*/, 
            INFINITE/* attendra ind�finiment jusqu'� ce que l'objet (threadHandle) atteigne l'�tat signal�*/);
        Exit();
    }
}

void Thread::Exit() {
    if (isRunning) {
        CloseHandle(threadHandle);
        isRunning = false;
    }
}