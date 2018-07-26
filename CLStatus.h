//
// Created by root on 18-7-25.
//

#ifndef LINUXPROGRAMMING_CLSTATUS_H
#define LINUXPROGRAMMING_CLSTATUS_H


class CLStatus {
public:

    /*
     * ReturnCode >= 0 indicates success, else fail
     */
    CLStatus(long ReturnCode, long ErrorCode);
    CLStatus(const CLStatus& s);
    virtual ~CLStatus();

public:
    bool IsSuccess();
    long GetErrorCode();

    const long& m_cReturnCode;
    const long& m_cErrorCode;

private:
    long m_ReturnCode;
    long m_ErrorCode;
};


#endif //LINUXPROGRAMMING_CLSTATUS_H
