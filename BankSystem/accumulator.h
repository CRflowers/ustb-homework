#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "date.h"

//Accumulator 积累类定义

class Accumulator{
private:
    Date lastDate;
    double value;   //要积累的值
    double sum;     //积累的和

public:
    Accumulator(Date date,double pValue);
    void change(Date newDate,double dValue);
    void reset(Date newDate,double newValue);

    double getSum(){
        return sum;
    }

};

#endif // ACCUMULATOR_H
