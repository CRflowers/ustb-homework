#ifndef SHOOT_H
#define SHOOT_H

#include "bullet.h"
#include "track.h"

class Shoot
{
public:
    Shoot();
    static int randInt(int a,int b);

    static QVector<Bullet*> noShoot(int t,QPointF pos);
    static QVector<Bullet*> y_linearShoot(int t,QPointF pos);
    static QVector<Bullet*> crossShoot(int t,QPointF pos);
    static QVector<Bullet*> randomShoot_1(int t,QPointF pos);
    static QVector<Bullet*> randomShoot_2(int t,QPointF pos);
    static QVector<Bullet*> bossShoot_1(int t,QPointF pos);
};

#endif // SHOOT_H
