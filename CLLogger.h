//
// Created by root on 18-7-26.
//

#ifndef LINUXPROGRAMMING_CLLOGGER_H
#define LINUXPROGRAMMING_CLLOGGER_H


#include "CLStatus.h"

class CLLogger {
public:
    CLLogger();
    virtual ~CLLogger();

    CLStatus WriteLog(const char * pstrMsg, long ErrorCode);

private:
    CLLogger(const CLLogger&);
    CLLogger& operator=(const CLLogger&);
};


#endif //LINUXPROGRAMMING_CLLOGGER_H
