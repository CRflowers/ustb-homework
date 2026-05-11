#include "bullet.h"

Bullet::Bullet(){
    t = 0;
}

/*
Bullet::Bullet(QString pixmap,double speed,QPointF direction) {
    this->setPixmap(pixmap);
    this->speed = speed;
    this->direction = direction;
}

Bullet::Bullet(QString pixmap){
    this->setPixmap(pixmap);
}
*/


void Bullet::setSpeed(double x,double y){
    this->speed = QPointF(x,y);
}

void Bullet::setSpeed(QPointF speed){
    this->speed = speed;
}

void Bullet::setTrack(std::function<QPointF(int t)> func){
    trackFunc = func;
}

void Bullet::update(){
    t++;
    //speed = Track::trackFunc(t);
    //qDebug() << t << Track::circleTrack(t);
    move();
    //其他行为...
}

void Bullet::move(){
    //qDebug() << trackFunc(t) << t;
    //qDebug() << this << t << speed;
    double dx =speed.x()*trackFunc(t).x();
    double dy =speed.y()*trackFunc(t).y();
    this->moveBy(dx,dy);
}
