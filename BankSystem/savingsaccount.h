#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "account.h"
#include "accumulator.h"

class SavingsAccount : public Account
{
    Q_OBJECT

private:
    double rate;
    Accumulator acc;

public:
    SavingsAccount(Date date,string pid,double prate);

    void deposit(Date date,double amount,string desc);
    void withdraw(Date date,double amount,string desc);
    void settle(Date date);

    QString showText(){
        return "[储蓄卡]"+QString::fromStdString(getId())+"\t余额："+QString::number(getBalance());
    };

    double getRate(){
        return rate;
    }

    string getAccountForm() const{
        return "savingsAccount";
    }

    bool testWithdraw(double amount);

};

#endif // SAVINGSACCOUNT_H
