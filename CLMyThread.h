//
// Created by root on 8/2/18.
//

#ifndef LINUXPROGRAMMING_CLMYTHREAD_H
#define LINUXPROGRAMMING_CLMYTHREAD_H


#include "CLThread.h"

class CLMyThread : public CLThread{
public:
    virtual CLStatus RunThreadFunction();
};

#endif //LINUXPROGRAMMING_CLMYTHREAD_H
