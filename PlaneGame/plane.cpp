#include "plane.h"

Plane::Plane() {
}

void Plane::setSpeed(QPointF speed){
    this->speed = speed;
}

void Plane::setSpeed(double x,double y){
    this->speed = QPointF(x,y);
}


void Plane::appendBullet(Bullet* newBullet){
    bullet.append(newBullet);
}

/*
void Plane::shootBullet(Bullet* bullet,double speed = 5,int bulletCD = 20){

}
*/

bool Plane::canShoot(){
    return bulletCD <= 0;
}

void Plane::setBulletCD(int cd){
    bulletCD = cd;
}

int Plane::getBulletCD(){
    return bulletCD;
}

void Plane::removeBullet(int index){
    this->bullet.remove(index);
}

QVector<Bullet*>& Plane::getBullet(){
    return bullet;
}

QPointF Plane::getSpeed(){
    return speed;
}
