#ifndef WAVE_H
#define WAVE_H

#include "enemyplane.h"

class Wave
{
public:
    Wave();
    static int randInt(int a,int b);

    //预设波次
    static QVector<EnemyPlane*> wave0();
    static QVector<EnemyPlane*> wave1();
    static QVector<EnemyPlane*> wave2();
    static QVector<EnemyPlane*> wave3();
    static QVector<EnemyPlane*> wave4();
    static QVector<EnemyPlane*> wave5();
    static QVector<EnemyPlane*> wave6();
    static QVector<EnemyPlane*> wave7();
    static QVector<EnemyPlane*> wave8();
    static QVector<EnemyPlane*> boss1();

};

#endif // WAVE_H
