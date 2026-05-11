#include "enemyplane.h"


EnemyPlane::EnemyPlane(){
    setSpeed(0,0);                   //敌机初始静止
}

EnemyPlane::EnemyPlane(double x,double y){
    setSpeed(x,y);                   //传入初始速度，速度可调
}

EnemyPlane::EnemyPlane(QPointF speed){
    setSpeed(speed.x(),speed.y());                   //传入初始速度，速度可调
}

void EnemyPlane::setTrack(std::function<QPointF(int t)> func){
    trackFunc = func;
}

void EnemyPlane::setShoot(std::function<QVector<Bullet*>(int t,QPointF pos)> func){
    shootFunc = func;
}

void EnemyPlane::move(){
    double dx =getSpeed().x()*trackFunc(t).x();
    double dy =getSpeed().y()*trackFunc(t).y();
    this->moveBy(dx,dy);
}

QVector<Bullet*> EnemyPlane::shootBullet(){
    float x = this->pixmap().width();
    float y = this->pixmap().height();
    QVector<Bullet*> newBullets = shootFunc(t,QPointF(this->x()+x/2.0,this->y()+y));
    for(auto it = newBullets.begin();it != newBullets.end();it++){
        appendBullet(*it);
    }

    t++;
    return newBullets;
}
