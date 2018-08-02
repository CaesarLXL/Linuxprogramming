//
// Created by root on 8/2/18.
//

#include <iostream>
#include "CLMyThread.h"

CLStatus CLMyThread::RunThreadFunction() {
    long i = (long)m_pContext;
    std::cout << i << std::endl;
    return CLStatus(0, 0);
}
