#include "account.h"
#include <cmath>
using namespace std;

double Account::total = 0;  //静态成员变量初始化
multimap<Date, AccountRecord> Account::recordMap;

//Account 账户类实现

Account::Account(Date date,string pId,double pBalance){
    id = pId;
    balance = pBalance;
    createDate = date;
}

Account::~Account(){

}

void Account::record(Date date,double amount,QString desc){
    amount = floor(amount*100+0.5)/100;
    balance += amount;

    recordMap.insert(make_pair(date,AccountRecord(date,this,amount,balance,desc.toStdString())));

    //这里，发射一个信号，让界面显示记录
    emit accountRecordSignal(date,QString::fromStdString(id),amount,balance,desc);

    total += amount;
}

void Account::query(Date day1,Date day2){
    multimap<Date,AccountRecord>::iterator pos = recordMap.end()--;
    while(pos != recordMap.begin()){
        if((day1 <= pos->first) && (pos->first <= day2)){        //日期大于day1小于day2
            pos->second.show();
        }
        pos--;
    }
    pos->second.show();
}
