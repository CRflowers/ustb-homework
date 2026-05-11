#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>
#include "bullet.h"
#include <QVector>
#include <QPointF>

#include "track.h"
#include "shoot.h"

class Plane : public QGraphicsPixmapItem
{
private:
    QPointF speed;     //飞机的速度，是一个向量
    double hp;              //飞机的血量

    bool shoot = false;
    QVector<Bullet*> bullet;        //飞机的子弹
    int bulletCD = 0;              //子弹CD


public:
    void setSpeed(QPointF speed);
    void setSpeed(double x,double y);

    QPointF getSpeed();

    bool isShoot(){return shoot;}
    double getHp(){return hp;}

    void setShoot(bool x){shoot = x;}
    void setHp(double x){hp = x;}

    void appendBullet(Bullet* newBullet);
    virtual QVector<Bullet*> shootBullet() = 0;     //发射子弹，向飞机的朝向方向
    QVector<Bullet*>& getBullet();
    void removeBullet(int index);            //移除子弹

    bool canShoot();                //判读能否发射子弹
    int getBulletCD();
    void setBulletCD(int cd);       //设置发射cd

    bool collision(Bullet* bullet); //碰撞检测，后续看要不要实现

    Plane();

};

#endif // PLANE_H
