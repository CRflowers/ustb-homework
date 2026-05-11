#include "playerplane.h"

PlayerPlane::PlayerPlane() {
    setSpeed(4,4);      //初始单位速度
    powerUpSound = new QSoundEffect();
    powerUpSound->setSource(QUrl::fromLocalFile(":/sounds/resources/power_up.wav"));
}

QGraphicsPixmapItem* PlayerPlane::initCenter(){
    QPixmap pixmap(":/images/resources/center.png");
    pixmap = pixmap.scaled(10,10,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    center = new QGraphicsPixmapItem();
    center->setPixmap(pixmap);
    center->setPos(x()+16,y()+28);
    center->setZValue(2);

    return center;
}

QGraphicsPixmapItem* PlayerPlane::initRealCenter(){
    QPixmap pixmap(":/images/resources/real_center.png");
    pixmap = pixmap.scaled(1,1,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    realCenter = new QGraphicsPixmapItem();
    realCenter->setPixmap(pixmap);
    realCenter->setPos(x()+16+0.5,y()+28+0.5);
    realCenter->setZValue(0);

    return realCenter;
}

void PlayerPlane::update(){
    //无敌时间减少1帧
    if(unmatched){
        unmatchedCD--;
        if(unmatchedCD % 10>= 8){
            setPixmap(QPixmap(":/images/resources/me1_alpha.png"));
        }
        else{
            setPixmap(QPixmap(":/images/resources/me1.png").scaled(45,66,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }
        if(unmatchedCD <= 0){
            unmatched = false;
            unmatchedCD = 120;
        }
    }

    //移动
    move();
}

void PlayerPlane::move(){
    double dx = getSpeed().x();
    double dy = getSpeed().y();
    dx = dx*(isRight()-isLeft());
    dy = dy*(isDown()-isUp());
    this->moveBy(dx,dy);
    center->moveBy(dx,dy);
    realCenter->moveBy(dx,dy);

}

QVector<Bullet*> PlayerPlane::shootBullet(){
    QVector<Bullet*> newBullets = {};
    if(power < 2){
        Bullet* newBullet = new Bullet();
        newBullet->setPixmap(QPixmap(":/images/resources/bullet0.png").scaled(18,27));
        double x = this->x()+this->pixmap().width()/2-newBullet->pixmap().width()/2+1;
        double y = this->y()-newBullet->pixmap().height();
        newBullet->setSpeed(0,-20);
        newBullet->setDamage(1);
        newBullet->setTrack(Track::y_linearTrack);
        newBullet->setPos(x,y);
        newBullet->setZValue(2);

        newBullets.append(newBullet);
        appendBullet(newBullet);
    }
    else if(power >= 2){
        if(powerLevel==1){
            powerLevel++;
            powerUpSound->play();
        }
            Bullet* newBulletL = new Bullet();
            Bullet* newBulletR = new Bullet();
            newBulletL->setPixmap(QPixmap(":/images/resources/bullet0.png").scaled(18,27));
            newBulletR->setPixmap(QPixmap(":/images/resources/bullet0.png").scaled(18,27));
            double x = this->x()+this->pixmap().width()/2-newBulletL->pixmap().width()/2+1;
            double y = this->y()-newBulletL->pixmap().height();
            newBulletL->setSpeed(0,-20);
            newBulletL->setDamage(power-1);
            newBulletL->setTrack(Track::y_linearTrack);
            newBulletL->setPos(x-15,y);
            newBulletL->setZValue(2);
            newBulletR->setSpeed(0,-20);
            newBulletR->setDamage(power-1);
            newBulletR->setTrack(Track::y_linearTrack);
            newBulletR->setPos(x+15,y);
            newBulletR->setZValue(2);
            newBullets.append(newBulletL);
            newBullets.append(newBulletR);
            appendBullet(newBulletL);
            appendBullet(newBulletR);
    }
    //设置cd
    setBulletCD(5);

    return newBullets;
}
