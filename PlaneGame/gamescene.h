#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QTimer>

#include <QMouseEvent>  //鼠标事件
#include <QKeyEvent>    //键盘事件

#include <QSoundEffect>//音效

#include "background.h"
#include "playerplane.h"
#include "enemyplane.h"
#include "power.h"
#include "wave.h"


class GameScene : public QGraphicsScene
{
private:
    bool isUpdate = true;                   //是否更新
    long long time;                         //游戏时间（毫秒）
    int waveCount = 0;                      //波次
    Background* background;                 //背景控件
    QGraphicsTextItem* scoreText;           //得分显示
    QVector<QGraphicsPixmapItem*> lifePixmap; //残机显示
    QGraphicsTextItem* powerText;           //灵力显示
    QVector<Power*> power;                  //灵力掉落
    QGraphicsPixmapItem* gameover;          //游戏结束提示

    QVector<std::function<QVector<EnemyPlane*>()>> waveLst
        = {Wave::wave0,Wave::wave1,Wave::wave2,Wave::wave3,Wave::wave4,
        Wave::wave5,Wave::wave6,Wave::wave7,Wave::boss1};        //波次列表

    QTimer timer;                           //计时器
    PlayerPlane* playerPlane;               //玩家的飞机
    QVector<EnemyPlane*> enemyPlane;        //敌人的飞机
    QVector<Bullet*> playerBullet;          //玩家的子弹
    QVector<Bullet*> enemyBullet;           //敌人的子弹

public:
    explicit GameScene(QObject *parent = nullptr);
    void update();  //更新游戏(10ms)

    static bool allInScreen(QGraphicsPixmapItem* item);
    static bool notInScreen(QGraphicsPixmapItem* item);
    static bool upInScreen(QGraphicsPixmapItem* item);
    static bool downInScreen(QGraphicsPixmapItem* item);
    static bool leftInScreen(QGraphicsPixmapItem* item);
    static bool rightInScreen(QGraphicsPixmapItem* item);

    //音效
    QSoundEffect* damageSound;
    QSoundEffect* itemSound;
    QSoundEffect* grazeSound;
    QSoundEffect* shootSound;
    QSoundEffect* breakSound;
    QSoundEffect* playerDeadSound;

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};

#endif // GAMESCENE_H
