#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "plane.h"

class EnemyPlane : public Plane
{
public:
    QVector<Bullet*> shootBullet();
    void move();

    std::function<QPointF(int t)> trackFunc;    //轨迹函数
    std::function<QVector<Bullet*>(int t,QPointF)> shootFunc;   //射击方式函数

    void setTrack(std::function<QPointF(int t)> func);
    void setShoot(std::function<QVector<Bullet*>(int t,QPointF pos)> func);

    EnemyPlane();
    EnemyPlane(double x,double y);
    EnemyPlane(QPointF speed);

    void setWithPower(bool x){withPower = x;}

    bool isWithPower(){return withPower;}

private:
    bool withPower;         //是否携带灵力
    int t;       //飞机的时间变量，发射方式是t的函数，单位为帧

};

#endif // ENEMYPLANE_H
