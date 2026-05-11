#include "creditaccount.h"
#include <QDebug>

//CreditAccount 信用卡账户类类实现

CreditAccount::CreditAccount
    (Date date,string pid,double pcredit,double prate,double pfee)
    :Account(date,pid,0),rate(prate),acc(date,0),credit(pcredit),fee(pfee){

}

void CreditAccount::deposit(Date date,double amount,string desc){
    record(date,amount,QString::fromStdString(desc));

    acc.change(date,min(amount,-1*getBalance())*rate);
    //积累每日欠款。如果存款后仍为负值，积累新的每日欠款(amount)，否则积累0(balance-balance)
}

void CreditAccount::withdraw(Date date,double amount,string desc){
    deposit(date,-1*amount,desc);
}

void CreditAccount::settle(Date date){
    if(date.getDay() != 1){
        return ;                                    //只在每月1日调用
    }

    acc.change(date,0);
    if(getBalance()<0){                             //存款<0才结算利息
        record(date,acc.getSum(),"利息");       //总积累欠款 = 总每日欠款
    }

    if(date.getMonth() == 1 && date.getDay() == 1){
        record(date,-1*fee,"年费");               //年费
    }

    acc.reset(date,min(0.,getBalance()*rate));
}

bool CreditAccount::testWithdraw(double amount){
    if(amount-getBalance()<=credit){
        return true;
    }
    else{
        return false;
    }
}
