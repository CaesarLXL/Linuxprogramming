//
// Created by root on 18-7-25.
//

#include "CLStatus.h"


CLStatus::CLStatus(long ReturnCode, long ErrorCode) : m_cReturnCode(m_ReturnCode), m_cErrorCode(m_ErrorCode) {
    m_ReturnCode = ReturnCode;
    m_ErrorCode = ErrorCode;
}

CLStatus::~CLStatus() {

}

bool CLStatus::IsSuccess() {
    if (m_ReturnCode >= 0) {
        return true;
    } else {
        return false;
    }
}

CLStatus::CLStatus(const CLStatus &s) : m_cReturnCode(m_ReturnCode), m_cErrorCode(m_ErrorCode) {
    m_ReturnCode = s.m_ReturnCode;
    m_ErrorCode = s.m_ErrorCode;
}

long CLStatus::GetErrorCode() {
    return m_ErrorCode;
}