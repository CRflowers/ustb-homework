#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "account.h"
#include "accumulator.h"

class CreditAccount : public Account
{
    Q_OBJECT

private:
    double rate;
    Accumulator acc;
    double credit;
    double fee;

public:
    CreditAccount(Date date,string pid,double pcredit,double prate,double fee);

    void deposit(Date date,double amount,string desc);
    void withdraw(Date date,double amount,string desc);
    void settle(Date date);

    QString showText(){
        return "[信用卡]"+QString::fromStdString(getId())+"\t余额："+QString::number(getBalance())
            +"\t可用额度："+QString::number(getAvailableCredit());
    };

    double getRate(){
        return rate;
    }

    double getCredit(){
        return credit;
    }

    double getAvailableCredit(){
        if(getBalance()<0){
            return (credit+getBalance());
        }
        else{
            return credit;
        }

    }

    double getFee(){
        return fee;
    }

    string getAccountForm() const{
        return "creditAccount";
    }

    bool testWithdraw(double amount);


};

#endif // CREDITACCOUNT_H
