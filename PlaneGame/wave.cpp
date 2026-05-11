#include "wave.h"

//窗口大小
#define w 480
#define h 700

//#include "bullet.h"
#include "track.h"
#include "shoot.h"

//返回一个a到b之间的随机整数
int Wave::randInt(int a,int b){
    int num = a+(rand()%(b-a));
    return num;
}

Wave::Wave() {
}

QVector<EnemyPlane*> Wave::wave0(){
    //设置随机种子
    srand(std::time(0));

    QVector<EnemyPlane*> enemys = {};
    //测试区
    //start

    //end
    return enemys;
}

QVector<EnemyPlane*> Wave::wave1(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=0;i<w;i+=w/8){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy1.png"));
        enemy->setTrack(Track::y_linearTrack);
        enemy->setSpeed(0,1);
        enemy->setHp(5);
        enemy->setWithPower(false);

        enemy->setPos(i,-i-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::noShoot);

        enemys.append(enemy);
    }

    return enemys;
}

QVector<EnemyPlane*> Wave::wave2(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=w-w/8;i>0;i-=w/8){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy1.png"));
        enemy->setTrack(Track::y_linearTrack);
        enemy->setSpeed(0,1);
        enemy->setHp(5);
        enemy->setWithPower(true);

        enemy->setPos(w-i,-i-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::noShoot);

        enemys.append(enemy);
    }

    return enemys;
}

QVector<EnemyPlane*> Wave::wave3(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=0;i<w;i+=w/8){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy1.png"));
        enemy->setTrack(Track::y_linearTrack);
        enemy->setSpeed(0,1);
        enemy->setHp(5);
        enemy->setWithPower(true);

        enemy->setPos(i,-i-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::y_linearShoot);

        enemys.append(enemy);
    }

    return enemys;
}

QVector<EnemyPlane*> Wave::wave4(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=w-w/8;i>0;i-=w/8){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy1.png"));
        enemy->setTrack(Track::y_linearTrack);
        enemy->setSpeed(0,1);
        enemy->setHp(5);
        enemy->setWithPower(true);

        enemy->setPos(w-i,-i-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::y_linearShoot);

        enemys.append(enemy);
    }

    return enemys;
}

QVector<EnemyPlane*> Wave::wave5(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=2;i<8;i+=3){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy3.png"));
        enemy->setTrack(Track::y_linear_stopTrack);
        enemy->setSpeed(0,5);
        enemy->setHp(50);
        enemy->setWithPower(true);

        enemy->setPos(i*60,-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::crossShoot);

        enemys.append(enemy);
    }
    return enemys;
}

QVector<EnemyPlane*> Wave::wave6(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=2;i<8;i+=3){
        EnemyPlane* enemy = new EnemyPlane();
        enemy->setPixmap(QPixmap(":/images/resources/enemy3.png"));
        enemy->setTrack(Track::y_linear_stopTrack);
        enemy->setSpeed(0,5);
        enemy->setHp(50);
        enemy->setWithPower(true);

        enemy->setPos(i*60,-200);
        enemy->setZValue(2);
        enemy->setShoot(Shoot::randomShoot_1);

        enemys.append(enemy);
    }
    return enemys;
}

QVector<EnemyPlane*> Wave::wave7(){
    QVector<EnemyPlane*> enemys = {};
    for(int i=0;i<w;i+=w/8){
        for(int j = 0;j < 6;j++){
            EnemyPlane* enemy = new EnemyPlane();
            enemy->setPixmap(QPixmap(":/images/resources/enemy2.png"));
            enemy->setTrack(Track::linearTrack);
            enemy->setSpeed(0,1);
            enemy->setHp(6);
            enemy->setWithPower(true);

            enemy->setPos(i,-100-40*j);
            enemy->setZValue(2);
            enemy->setShoot(Shoot::y_linearShoot);

            enemys.append(enemy);
        }
    }
    return enemys;
}

QVector<EnemyPlane*> Wave::boss1(){
    QVector<EnemyPlane*> enemys = {};

    EnemyPlane* enemy = new EnemyPlane();
    enemy->setPixmap(QPixmap(":/images/resources/boss1.png"));
    enemy->setTrack(Track::y_linear_stopTrack);
    enemy->setSpeed(0,5);
    enemy->setHp(200);
    enemy->setWithPower(true);

    enemy->setPos(200,-200);
    enemy->setZValue(2);
    enemy->setShoot(Shoot::bossShoot_1);

    enemys.append(enemy);


    return enemys;
}
