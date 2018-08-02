//
// Created by root on 8/1/18.
//

#ifndef LINUXPROGRAMMING_CLTHREAD_H
#define LINUXPROGRAMMING_CLTHREAD_H


#include <zconf.h>
#include "CLStatus.h"
#include <pthread.h>

class CLThread {
public:
    CLThread();
    virtual ~CLThread();

    CLStatus Run(void *pContext=0);
    CLStatus WaitForDeath();

private:
    static void* StartFunctionOfThread(void *pThis);

protected:
    virtual CLStatus RunThreadFunction() = 0;

protected:
    void* m_pContext;
    pthread_t m_ThreadId;
};


#endif //LINUXPROGRAMMING_CLTHREAD_H
