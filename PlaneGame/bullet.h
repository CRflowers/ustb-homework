#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <functional>

#include "track.h"

class Bullet : public QGraphicsPixmapItem
{
private:
    QPointF speed;   //子弹的速度，二维向量
    double damage;   //子弹的伤害
    int t;       //子弹的时间变量，子弹的属性都是t的函数，单位为帧
    std::function<QPointF(int t)> trackFunc;    //轨迹函数

public:
    Bullet();
    //Bullet(QString pixmap);
    //Bullet(QString pixmap,double speed,QPointF direction);
    void setSpeed(double x,double y);
    void setSpeed(QPointF Speed);
    void setDamage(double x){damage = x;};

    double getDamage(){return damage;};

    void setTrack(std::function<QPointF(int t)> trackFunc);

    void update();  //更新子弹状态
    void move();

};

#endif // BULLET_H
