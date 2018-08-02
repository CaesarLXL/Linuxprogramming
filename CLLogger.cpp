//
// Created by root on 18-7-26.
//

#include <cstring>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include "CLLogger.h"

#define LOG_FILE_NAME "CLLogger.txt"
#define MAX_SIZE 265
#define BUFFER_SIZE_LOG_FILE 4096

CLLogger* CLLogger::m_pLog = nullptr;

CLLogger::CLLogger() {
    m_fd = open(LOG_FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    m_pLogBuffer = new char[BUFFER_SIZE_LOG_FILE];
    m_nUsedBytesForBuffer = 0;
    m_bFlagForProcessExit = false;
}

CLLogger::~CLLogger() {
    if (m_fd != -1) {
        close(m_fd);
    }
}

CLStatus CLLogger::WriteLog(const char *pstrMsg, long ErrorCode) {
    if (pstrMsg == nullptr) {
        return CLStatus(-1, 0);
    }

    if (strlen(pstrMsg) == 0) {
        return CLStatus(-1, 0);
    }

    if (m_fd == -1) {
        return CLStatus(-1, errno);
    }

    unsigned int nleftroom = m_nUsedBytesForBuffer - m_nUsedBytesForBuffer;
    size_t len_strmsg = strlen(pstrMsg);

    char buf[MAX_SIZE];
    snprintf(buf, MAX_SIZE, "Error code : %ld\r\n", ErrorCode);
    size_t len_code = strlen(buf);

    size_t total_len = len_strmsg + len_code;

    //msg > BUFFER_SIZE_LOG_FILE
    if (total_len > BUFFER_SIZE_LOG_FILE || m_bFlagForProcessExit) {

        if (m_fd == -1) {
            return CLStatus(-1, 0);
        }

        CLStatus s = Flush();
        if (!s.IsSuccess()) {
            return CLStatus(-1, 0);
        }

        ssize_t r = write(m_fd, pstrMsg, len_strmsg);
        if (r == -1) {
            return CLStatus(-1, errno);
        }

        r = write(m_fd, buf, len_code);
        if (r == -1) {
            return CLStatus(-1, errno);
        }

        return CLStatus(0, 0);
    }


    if (total_len > nleftroom) {
        CLStatus s = Flush();
        if (!s.IsSuccess()) {
            return CLStatus(-1, 0);
        }
    }

    memcpy(m_pLogBuffer + m_nUsedBytesForBuffer, pstrMsg, len_strmsg);
    m_nUsedBytesForBuffer += len_strmsg;

    memcpy(m_pLogBuffer + m_nUsedBytesForBuffer, buf, len_code);
    m_nUsedBytesForBuffer += len_code;

    close(m_fd);

    return CLStatus(0, 0);
}

CLLogger *CLLogger::GetInstance() {
    if (m_pLog == nullptr) {
        m_pLog = new CLLogger;

        if (atexit(CLLogger::OnProcessExit) != 0) {
            if (m_pLog != nullptr) {
                m_pLog->WriteLog("In CLLoger::GetInstance(), atexit error", errno);
                m_pLog->Flush();
            }
        }
    }
    return m_pLog;
}

CLStatus CLLogger::WriteLogMsg(const char *pstrMsg, long ErrorCode) {
    CLLogger *pLog = CLLogger::GetInstance();
    if (pLog == nullptr) {
        return CLStatus(-1, 0);
    }

    CLStatus s = pLog->WriteLog(pstrMsg, ErrorCode);

    if (!s.IsSuccess()) {
        return CLStatus(0, 0);
    } else {
        return CLStatus(-1, 0);
    }
}

CLStatus CLLogger::Flush() {
    if (m_fd == -1) {
        return CLStatus(-1, 0);
    }

    if (m_pLogBuffer == nullptr) {
        return CLStatus(-1, 0);
    }

    if (m_nUsedBytesForBuffer == 0) {
        return CLStatus(0, 0);
    }

    ssize_t r = write(m_fd, m_pLogBuffer, m_nUsedBytesForBuffer);
    if (r == -1) {
        return CLStatus(-1, errno);
    }

    m_nUsedBytesForBuffer = 0;

    return CLStatus(0, 0);
}

void CLLogger::OnProcessExit() {
    CLLogger *pLogger = CLLogger::GetInstance();
    if (pLogger != nullptr) {
        pLogger->Flush();
        pLogger->m_bFlagForProcessExit = true;
    }
}
