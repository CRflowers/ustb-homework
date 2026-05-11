#include "date.h"
#include <string>
using namespace std;

const int monthDay[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int isLeapYear(int year){
    if( (year%400 == 0) || ((year%4 == 0)&&(year%100 != 0)) ){
        return 1;
    }
    else{
        return 0;
    }
}


Date::Date(int y,int m,int d){
    year = y;
    month = m;
    day = d;
}

Date Date::read(){
    string date;
    //cin >> date;需要改

    int pos = 0,y = 0,m = 0,d = 0;
    while(date[pos] != '/'){
        y *= 10;
        y += int(date[pos])-48;
        pos++;
    }
    pos++;
    while(date[pos] != '/'){
        m *= 10;
        m += int(date[pos])-48;
        pos++;
    }
    pos++;
    while(pos != int(date.length())){
        d *= 10;
        d += int(date[pos])-48;
        pos++;
    }
    return Date(y,m,d);             //别问我为什么减48。你测试一下就知道了。
}

int Date::distance(Date lastDate){
    int totalDays;
    int left = 0;
    int right = 0;
    int mid = 0;

    for(int i=1;i<lastDate.month;i++){      //左侧不完整一年left
        left += monthDay[i];
    }
    left += lastDate.day;
    if(isLeapYear(lastDate.year)){      //判断闰年
        if(lastDate > Date(lastDate.year,2,29)){
            left++;
        }
        left = 366 - left;
    }
    else{
        left = 365 - left;
    }


    for(int i=1;i<month;i++){               //右侧不完整一年right
        right += monthDay[i];
    }
    right += day;
    if(isLeapYear(year)){      //判断闰年
        if(lastDate <= Date(lastDate.year,2,29)){
            right++;
        }
    }

    //中间完整年份
    mid = year - lastDate.year - 1;
    mid *= 365;

    for(int i = lastDate.year+1; i <= year-1; i++){      //判断是否需要加闰年
        mid += isLeapYear(i);
    }

    totalDays = left + right +mid;

    return totalDays;
}


int Date::monthDistance(Date lastDate){
    return (12 * (year-lastDate.year) + (month-lastDate.month));
}


QString Date::showText(){
    return QString::number(year)+"年"+QString::number(month)+"月"+
           QString::number(day)+"日";
}

void Date::nextYear(){
    year++;month=1;day=1;
}

void Date::nextMonth(){
    if(month == 12){
        nextYear();
    }
    else{
        month++;day=1;
    }
}

void Date::nextDay(){
    if(day == monthDay[month]){
        nextMonth();
    }
    else{
        day++;
    }
}

void Date::changeDate(int y,int m,int d){
    year=y;month=m;day=d;
}

bool Date::isLeapMonth(){
    if(isLeapYear(year) && month == 2){
        return true;
    }
    else{
        return false;
    }
}

int Date::getMaxDay(){   //返回这个月的最大天数
    if(isLeapMonth()){
        return monthDay[month]+1;
    }
    else{
        return monthDay[month];
    }
}
