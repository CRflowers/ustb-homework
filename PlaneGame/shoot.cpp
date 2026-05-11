#include "shoot.h"
#include <cmath>

//返回一个a到b之间的随机整数
int Shoot::randInt(int a,int b){
    int num = a+(rand()%(b-a));
    return num;
}

Shoot::Shoot() {}

//预设射击方式
QVector<Bullet*> Shoot::noShoot(int t,QPointF pos){
    if(t%180==0){}
    if(pos==QPointF(0,0)){}
    return {};
}

QVector<Bullet*> Shoot::y_linearShoot(int t,QPointF pos){
    QVector<Bullet*> bullets = {};
    if(t % 120 == 0){
        Bullet* bullet = new Bullet();
        bullet->setPixmap(QPixmap(":/images/resources/bullet1.png").scaled(20,20));
        bullet->setPos(pos);
        bullet->setZValue(2);
        bullet->setSpeed(0,2);
        bullet->setTrack(Track::y_linearTrack);
        bullets.append(bullet);
    }
    return bullets;
}

QVector<Bullet*> Shoot::crossShoot(int t,QPointF pos){
    QVector<Bullet*> bullets = {};
    if(t % 20 == 0){
        Bullet* bullet = new Bullet();
        bullet->setPixmap(QPixmap(":/images/resources/bullet1.png").scaled(20,20));
        bullet->setPos(pos);
        bullet->setZValue(2);
        bullet->setSpeed(3*cos(t/40.0*M_PI),3*sin(t/40.0*M_PI));
        bullet->setTrack(Track::linearTrack);
        bullets.append(bullet);
    }
    return bullets;
}

QVector<Bullet*> Shoot::randomShoot_1(int t,QPointF pos){
    QVector<Bullet*> bullets = {};
    if(t % 30 == 0){
        Bullet* bullet = new Bullet();
        bullet->setPixmap(QPixmap(":/images/resources/bullet1.png").scaled(20,20));
        bullet->setPos(pos);
        bullet->setZValue(2);
        bullet->setSpeed(5*Shoot::randInt(-100,101)/100.0,5*Shoot::randInt(0,101)/100.0);
        bullet->setTrack(Track::linearTrack);
        bullets.append(bullet);
    }
    return bullets;
}

QVector<Bullet*> Shoot::randomShoot_2(int t,QPointF pos){
    QVector<Bullet*> bullets = {};
    if(t % 30 == 0){
        Bullet* bullet = new Bullet();
        bullet->setPixmap(QPixmap(":/images/resources/bullet2.png").scaled(20,20));
        bullet->setPos(pos);
        bullet->setZValue(2);
        bullet->setSpeed(25*Shoot::randInt(-20,21)/20.0,5*Shoot::randInt(30,101)/100.0);
        bullet->setTrack(Track::randomTrack);
        bullets.append(bullet);
    }
    return bullets;
}

QVector<Bullet*> Shoot::bossShoot_1(int t,QPointF pos){
    QVector<Bullet*> bullets = {};
    if(t % 20 == 0){
        for(int i = 0;i < 16;i++){
            Bullet* bullet = new Bullet();
            bullet->setPixmap(QPixmap(":/images/resources/bullet1.png").scaled(20,20));
            bullet->setPos(pos);
            bullet->setZValue(2);
            bullet->setSpeed(5*cos(i/8.0*M_PI+t/100.0*M_PI),5*sin(i/8.0*M_PI+t/100.0*M_PI));
            bullet->setTrack(Track::linearTrack);
            bullets.append(bullet);
        }
    }
    return bullets;
}
