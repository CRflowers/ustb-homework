#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <string>
#include <QString>
#include <QmultiMap>
#include "date.h"
#include "accountrecord.h"

using namespace std;

class Account:public QObject
{
    Q_OBJECT

private:
    std::string id;
    double balance;
    Date createDate;
    static double total;
    static multimap<Date, AccountRecord> recordMap;

public:
    Account(Date date,string pId,double pBalance);
    ~Account();
    void record(Date date,double amount,QString desc);   //记录账目
    static void query(Date day1,Date day2);                    //查询账目

    virtual void deposit(Date date,double amount,string desc) = 0;
    virtual void withdraw(Date date,double amount,string desc) = 0;
    virtual void settle(Date date) = 0;

    std::string getId() const{
        return id;
    }

    double getBalance(){
        return balance;
    }

    static double getTotal(){
        return total;
    }

    virtual QString showText() = 0;          //返回展示文本，不同派生类的文本不一样

    virtual string getAccountForm() const = 0;
    virtual bool testWithdraw(double amount) = 0;      //测试一次取钱能否成功

signals:
    //发射信号，显示在界面上
    void accountRecordSignal(Date _date,QString _id,double _amount,double _balance,QString _desc);
};

#endif // ACCOUNT_H
