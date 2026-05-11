#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "plane.h"

#include <QDebug>
#include <QPoint>
#include <QKeyEvent>

#include <QSoundEffect>


class PlayerPlane : public Plane
{
private:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shift = false;     //低速
    bool unmatched = false; //无敌
    int unmatchedCD = 120;  //无敌时间2s

    int score = 0;     //得分
    float life = 3;    //残机
    float power = 1.00;   //灵力
    QGraphicsPixmapItem* center;//判定点
    QGraphicsPixmapItem* realCenter;//真实判定点

public:
    PlayerPlane();
    //void move(QPoint event);

    bool isUp(){return up;}
    bool isDown(){return down;}
    bool isLeft(){return left;}
    bool isRight(){return right;}
    bool isUnmatched(){return unmatched;}
    bool isShift(){return shift;}

    void setUp(bool x){up = x;}
    void setDown(bool x){down = x;}
    void setLeft(bool x){left = x;}
    void setRight(bool x){right = x;}
    void setUnmatched(bool x){unmatched = x;}
    void setUnmatchedCD(int x){unmatchedCD = x;}
    void setShift(bool x){shift = x;}
    void setScore(int x){score = x;}

    void addScore(int x){score+=x;}
    int getScore(){return score;}
    int getLife(){return life;}
    float getPower(){return power;}

    void setLife(int x){life = x;}
    void lossALife(){life--;}
    void setPower(int x){power = x;}
    void addPower(float x){power += x;}

    QGraphicsPixmapItem* getCenter(){return center;}
    QGraphicsPixmapItem* getRealCenter(){return realCenter;}

    QGraphicsPixmapItem* initCenter();  //初始化判定点
    QGraphicsPixmapItem* initRealCenter();

    void update();
    void move();
    QVector<Bullet*> shootBullet();

    QSoundEffect* powerUpSound;
    int powerLevel = 1;

};

#endif // PLAYERPLANE_H
