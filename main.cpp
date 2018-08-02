#include <iostream>
#include "CLStatus.h"
#include "CLLogger.h"
#include "CLThread.h"
#include "CLMyThread.h"

using namespace std;

int main() {
    CLThread *pThread = new CLMyThread;
    pThread->Run((void*)2);
    pThread->WaitForDeath();
    delete pThread;
    return 0;
}