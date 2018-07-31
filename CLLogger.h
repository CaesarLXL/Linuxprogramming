//
// Created by root on 18-7-26.
//

#ifndef LINUXPROGRAMMING_CLLOGGER_H
#define LINUXPROGRAMMING_CLLOGGER_H


#include "CLStatus.h"

class CLLogger {
public:
    static CLLogger* GetInstance();
    static CLStatus WriteLogMsg(const char* pstrMsg, long ErrorCode);
    CLStatus WriteLog(const char * pstrMsg, long ErrorCode);
    CLStatus Flush();

private:
    CLLogger();
    CLLogger(const CLLogger&);
    CLLogger& operator=(const CLLogger&);
    virtual ~CLLogger();

private:
    static void OnProcessExit();

private:
    int m_fd;
    static CLLogger *m_pLog;

private:
    char *m_pLogBuffer;
    unsigned int m_nUsedBytesForBuffer;
};


#endif //LINUXPROGRAMMING_CLLOGGER_H
