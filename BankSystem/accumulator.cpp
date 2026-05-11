#include "accumulator.h"
#include <cmath>
#include <QDebug>

//Accumulator 积累类实现

Accumulator::Accumulator(Date date,double pValue):
    lastDate(date),value(floor(pValue*100+0.5)/100),sum(0){

}

void Accumulator::change(Date newDate,double dValue){   //积累一次，同时改变dValue这么多要积累的值
    sum += newDate.distance(lastDate) * value;
    lastDate = newDate;
    value += dValue;
    //cout << "value:" << value << "\tsum:" << sum << endl;
}

void Accumulator::reset(Date newDate,double newValue){  //重置 清零
    sum = 0;
    lastDate = newDate;
    value = newValue;
}
