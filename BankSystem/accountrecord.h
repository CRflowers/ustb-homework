#ifndef ACCOUNTRECORD_H
#define ACCOUNTRECORD_H

#include <string>
#include "date.h"
using namespace std;

class Account;

//AccountRecord 记录账户类定义

class AccountRecord{
private:
    Date date;
    const Account* account;
    double amount;
    double balance;
    string desc;

public:
    AccountRecord(Date pDate,const Account* pAccount,double pAmount,double pBalance,string pDesc);
    void show();

};

#endif // ACCOUNTRECORD_H
