#include "track.h"
#include <QDebug>

//返回一个a到b之间的随机整数
int Track::randInt(int a,int b){
    int num = a+(rand()%(b-a));
    return num;
}

Track::Track() {}

//预设轨迹
QPointF Track::x_linearTrack(int t){
    return QPointF(1,0*t);
}
QPointF Track::y_linearTrack(int t){
    return QPointF(0*t,1);
}
QPointF Track::linearTrack(int t){
    return QPointF(1+0*t,1+0*t);
}
QPointF Track::circleTrack(int t){
    return QPointF(cos(double(t)/100),sin(double(t)/100));
}
QPointF Track::y_linear_stopTrack(int t){
    if(t>=60){
        return QPointF(0,0);
    }
    else{
        return QPointF(0*t,1);
    }
}
QPointF Track::randomTrack(int t){
    return QPointF(Track::randInt(0,201)/100.0-1,Track::randInt(0,201)/100.0-1+0*t);
}
