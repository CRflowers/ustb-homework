#include "savingsaccount.h"

//SavingsAccount 储蓄卡账户类类实现

SavingsAccount::SavingsAccount(Date date,string pid,double prate)
    :Account(date,pid,0),rate(prate),acc(date,0){

}

void SavingsAccount::deposit(Date date,double amount,string desc){
    acc.change(date,amount);
    record(date,amount,QString::fromStdString(desc));
}

void SavingsAccount::withdraw(Date date,double amount,string desc){
    deposit(date,-1*amount,desc);
}

void SavingsAccount::settle(Date date){
    if(date.getMonth() != 1 || date.getDay() != 1){
        return ;                                //只在每年1月1日调用
    }

    acc.change(date,0);
    double amount = acc.getSum()/366*rate;      //总日均余额 = 总积累余额/366
    if(acc.getSum() > 0){
        record(date,amount,"利息");
    }

    acc.reset(date,getBalance());
}

bool SavingsAccount::testWithdraw(double amount){
    if(getBalance()-amount<0){
        return false;
    }
    else{
        return true;
    }
}
