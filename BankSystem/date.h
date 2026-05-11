#ifndef DATE_H
#define DATE_H

#include <QString>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date():year(0),month(0),day(0){}
    Date(int y,int m,int d);
    static Date read();             //读入一个日期xxxx/xx/xx，返回一个Date类对象
    int distance(Date lastDate);    //返回两天之间距离
    int monthDistance(Date lastDate);//返回两天之间月份相差距离

    bool operator < (const Date& date) const{                       //重载运算符，比较两天
        if(year < date.year){
            return true;
        }
        else if((year == date.year) && (month < date.month)){
            return true;
        }
        else if((year == date.year) && (month < date.month) && (day < date.day)){
            return true;
        }
        else{
            return false;
        }
    }

    bool operator == (const Date& date) const{                       //重载运算符，比较两天
        if(year == date.year && month == date.month && day == date.day){
            return true;
        }
        else{
            return true;
        }
    }

    bool operator != (const Date& date) const{                       //重载运算符，比较两天
        return !(*this == date);
    }

    bool operator <= (const Date& date) const{                       //重载运算符，比较两天
        //cout << year << ' ' << month << ' ' << day << endl << date.year << ' ' << date.month << ' ' << date.day << endl;
        if(*this < date || *this == date){
            return true;
        }
        else{
            return false;
        }
    }

    bool operator > (const Date& date) const{
        if(*this <= date){
            return false;
        }
        else{
            return true;
        }
    }

    bool operator()(const Date& a,const Date& b) const {
        return a < b;
    }

    QString showText();     //返回日期格式
    void nextYear();        //修改日期
    void nextMonth();
    void nextDay();
    void changeDate(int y,int m,int d);

    int getYear(){
        return year;
    }

    int getMonth(){
        return month;
    }

    int getDay(){
        return day;
    }

    bool isLeapMonth(); //判断当前所处月份是否为闰月
    int getMaxDay();    //返回这个月的最大天数

};

#endif // DATE_H
