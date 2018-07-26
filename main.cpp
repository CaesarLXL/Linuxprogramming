#include <iostream>
#include "CLStatus.h"
#include "CLLogger.h"

using namespace std;


CLStatus f() {
    CLStatus s(-1, 2);
    return s;
}

int main() {
    /*CLStatus s =f();
    if (!s.IsSuccess()) {
        cout << "f error" << endl;
        cout << "error code:" << s.GetErrorCode() << endl;
    }*/

    CLLogger logger;
    CLStatus s = logger.WriteLog("this is an error", 5);

    if (!s.IsSuccess()) {
        cout << "logger error" << endl;
    } else {
        cout << "logger success" << endl;
    }

    return 0;
}