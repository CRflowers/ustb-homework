#include "gamescene.h"
//#include <random>
#include <ctime>
#include <cstdlib>
#include <QFont>
#include <QTextFormat>

//游戏窗口大小
#define w_width 480
#define w_height 700

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}
{
    //背景
    background = new Background();
    background->setPixmap(QPixmap(":/images/resources/background1.png").scaled(480,1400));   //设置图像
    background->setPos(0,-700);
    background->setZValue(0);
    this->addItem(background);

    //音效
    damageSound = new QSoundEffect();
    damageSound->setSource(QUrl::fromLocalFile(":/sounds/resources/damage.wav"));
    itemSound = new QSoundEffect();
    itemSound->setSource(QUrl::fromLocalFile(":/sounds/resources/item.wav"));
    grazeSound = new QSoundEffect();
    grazeSound->setSource(QUrl::fromLocalFile(":/sounds/resources/graze.wav"));
    shootSound = new QSoundEffect();
    shootSound->setSource(QUrl::fromLocalFile(":/sounds/resources/shoot.wav"));
    breakSound = new QSoundEffect();
    breakSound->setSource(QUrl::fromLocalFile(":/sounds/resources/break.wav"));
    playerDeadSound = new QSoundEffect();
    playerDeadSound->setSource(QUrl::fromLocalFile(":/sounds/resources/loss_life.wav"));

    //自机
    playerPlane = new PlayerPlane();
    playerPlane->setPixmap(QPixmap(":/images/resources/me1.png").scaled(45,66,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //设置锚点为中心?
    //playerPlane->setTransformOriginPoint(playerPlane->boundingRect().center());
    //playerPlane->setTransformOriginPoint(51,63);
    playerPlane->setPos(240,550);
    playerPlane->setZValue(1);
    this->addItem(playerPlane);
    this->addItem(playerPlane->initCenter());
    this->addItem(playerPlane->initRealCenter());

    //信息栏
    QGraphicsPixmapItem* info = new QGraphicsPixmapItem();
    info->setPixmap(QPixmap(":/images/resources/info.png").scaled(393,700,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    info->setPos(475,0);
    info->setZValue(4);
    this->addItem(info);

    QFont font("Forte");
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    font.setPointSize(20);
    //得分
    scoreText = new QGraphicsTextItem();
    QString st = QString::number(playerPlane->getScore());
    for(int i=13;i>st.length();i--){
        st = "0"+st;
    }
    scoreText->setPlainText(st);
    scoreText->setFont(font);
    scoreText->setPos(650,40);
    scoreText->setZValue(5);
    this->addItem(scoreText);
    //残机
    for(int i=0;i<playerPlane->getLife();i++){
        QGraphicsPixmapItem* life = new QGraphicsPixmapItem();
        life->setPixmap(QPixmap(":/images/resources/life.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        life->setPos(650+30*i,180);
        life->setZValue(5);
        lifePixmap.append(life);
        this->addItem(life);
    }
    //灵力
    powerText = new QGraphicsTextItem();
    QString pt = QString::number(playerPlane->getPower(),'f',2);
    powerText->setPlainText(pt);
    powerText->setFont(font);
    powerText->setPos(650,240);
    powerText->setZValue(5);
    this->addItem(powerText);

    //游戏结束提示，先不加入场景
    gameover = new QGraphicsPixmapItem(QPixmap(":/images/resources/gameover.png"));
    gameover->setPos(40,270);
    gameover->setZValue(3);

    //连接时间戳与槽函数，在槽函数内实现各个游戏控件的更新
    connect(&timer,&QTimer::timeout,this,&GameScene::update);
    timer.start(16);    //设置16ms触发一次，打开计时器
}

//判断一个图形项有没有全部位于屏幕内，如飞机
bool GameScene::allInScreen(QGraphicsPixmapItem* item){
    QPixmap pixmap = item->pixmap();
    double x = item->x();
    double y = item->y();
    double w = pixmap.width();
    double h = pixmap.height();
    if(x >= 0 && y >= 0 && x+w <= w_width && y+h <= w_height){
        return true;
    }
    else{
        return false;
    }
}

//判断一个图形项有没有超出屏幕外，如子弹
bool GameScene::notInScreen(QGraphicsPixmapItem* item){
    QPixmap pixmap = item->pixmap();
    double x = item->x();
    double y = item->y();
    double w = pixmap.width();
    double h = pixmap.height();
    if(x+w >= 0 && y+h >= 0 && x <= w_width && y <= w_height){
        return false;
    }
    else{
        return true;
    }
}

//四个方向
bool GameScene::upInScreen(QGraphicsPixmapItem* item){
    double y = item->y();
    if(y >= 0){return true;}
    else{return false;}
}
bool GameScene::downInScreen(QGraphicsPixmapItem* item){
    QPixmap pixmap = item->pixmap();
    double y = item->y();
    double h = pixmap.height();
    if(y+h <= w_height){return true;}
    else{return false;}
}
bool GameScene::leftInScreen(QGraphicsPixmapItem* item){
    double x = item->x();
    if(x >= 0){return true;}
    else{return false;}
}
bool GameScene::rightInScreen(QGraphicsPixmapItem* item){
    QPixmap pixmap = item->pixmap();
    double x = item->x();
    double w = pixmap.width();
    if(x+w <= w_width){return true;}
    else{return false;}
}

//更新游戏
void GameScene::update(){
    if(!isUpdate){
        return ;
    }

    time += 1;

    //背景流动
    background->stream();

    //自机移动，检查有没有移出屏幕范围，将移出去的那个方向设为false
    if(!upInScreen(playerPlane)){
        playerPlane->setUp(false);
    }
    if(!downInScreen(playerPlane)){
        playerPlane->setDown(false);
    }
    if(!leftInScreen(playerPlane)){
        playerPlane->setLeft(false);
    }
    if(!rightInScreen(playerPlane)){
        playerPlane->setRight(false);
    }
    playerPlane->update();

    //敌机移动，清除屏幕外的飞机
    {
    auto it = enemyPlane.begin();
    while(it != enemyPlane.end()){
        (*it)->move();
        if(notInScreen(*it) && upInScreen(*it)){
            //保存对象
            EnemyPlane* delEnemy = *it;
            //从场景中移除
            this->removeItem(*it);
            //从敌机容器中移除
            it = enemyPlane.erase(it);
            //释放内存
            delete delEnemy;
        }
        else{
            ++it;
        }
    }
    }

    //灵力移动，清除屏幕外的灵力
    {
        auto it = power.begin();
        while(it != power.end()){
            (*it)->move();
            if(notInScreen(*it) && upInScreen(*it)){
                //保存对象
                Power* delPower = *it;
                //从场景中移除
                this->removeItem(*it);
                //从敌机容器中移除
                it = power.erase(it);
                //释放内存
                delete delPower;
            }
            else{
                ++it;
            }
        }
    }

    //玩家发射子弹，处于cd时则减少一下
    if(playerPlane->canShoot() && playerPlane->isShoot()){
        QVector<Bullet*> newBullets = playerPlane->shootBullet();
        for(auto bulletIt = newBullets.begin();bulletIt != newBullets.end();bulletIt++){
            playerBullet.append(*bulletIt);
            this->addItem(*bulletIt);
        }
    }
    if(!playerPlane->canShoot()){
        playerPlane->setBulletCD(playerPlane->getBulletCD()-1);
    }

    //敌机发射子弹
    for(auto enemyIt = enemyPlane.begin();enemyIt!=enemyPlane.end();enemyIt++){
        QVector<Bullet*> newBullets = (*enemyIt)->shootBullet();
        for(auto bulletIt = newBullets.begin();bulletIt != newBullets.end();bulletIt++){
            enemyBullet.append(*bulletIt);
            this->addItem(*bulletIt);
        }
    }


    //遍历子弹列表（自机）
    //注释的是错误的，因为子弹和飞机不是依存关系，必须在scene里定义子弹容器
    //QVector<Bullet*>& playerBullet = playerPlane->getBullet();
    auto bulletIt = playerBullet.begin();
    while(bulletIt != playerBullet.end()){
        //更新子弹状态
        (*bulletIt)->update();
        //如果子弹出界，移除子弹
        if(notInScreen(*bulletIt)){
            //先保存
            Bullet* delBullet = *bulletIt;
            //从场景中移除
            this->removeItem(*bulletIt);
            //从飞机的子弹容器中移除
            bulletIt = playerBullet.erase(bulletIt);
            //释放内存
            delete delBullet;
        }
        else{
            ++bulletIt;
        }
    }

    //遍历子弹列表（敌机）
    bulletIt = enemyBullet.begin();
    while(bulletIt != enemyBullet.end()){
        //更新子弹状态
        (*bulletIt)->update();
        //如果子弹出界，移除子弹
        if(notInScreen(*bulletIt)){
            //先保存
            Bullet* delBullet = *bulletIt;
            //从场景中移除
            this->removeItem(*bulletIt);
            //从飞机的子弹容器中移除
            bulletIt = enemyBullet.erase(bulletIt);
            //释放内存
            delete delBullet;
        }
        else{
            ++bulletIt;
        }
    }


    //检测碰撞(自机与敌机)
    for(auto enemyIt = enemyPlane.begin();enemyIt != enemyPlane.end();enemyIt++){
        //碰撞("进入"判定点)，先判定是否在无敌，否则减一条命，进入无敌
        if((*enemyIt)->collidesWithItem(playerPlane->getRealCenter())){
            if(!playerPlane->isUnmatched()){
                playerPlane->lossALife();
                playerPlane->setUnmatched(true);
                this->removeItem(lifePixmap.back());
                delete lifePixmap.back();
                lifePixmap.pop_back();
                playerDeadSound->play();

                if(playerPlane->getLife()<=0){
                    isUpdate = false;
                    this->removeItem(playerPlane);
                    this->removeItem(playerPlane->getCenter());
                    this->removeItem(playerPlane->getRealCenter());
                    this->addItem(gameover);
                }
            }
        }
    }


    //检测碰撞(自机与灵力)
    auto powerIt = power.begin();
    while(powerIt != power.end()){
        //碰撞
        if((*powerIt)->collidesWithItem(playerPlane)){
            playerPlane->addPower(0.01);
            //碰撞，删除灵力
            QGraphicsPixmapItem* delPower = *powerIt;
            //从场景中移除
            this->removeItem(*powerIt);
            //从飞机的子弹容器中移除
            powerIt = power.erase(powerIt);
            //释放内存
            delete delPower;
            //设置新灵力
            powerText->setPlainText(QString::number(playerPlane->getPower(),'f',2));
            //播放音效
            itemSound->play();
        }
        else{
            powerIt++;
        }
    }


    //检测碰撞(敌机与子弹)
    auto enemyIt = enemyPlane.begin();
    while(enemyIt != enemyPlane.end()){
        //一定要把初始化写这里！！不然没法遍历
        auto bulletIt = playerBullet.begin();
        while(bulletIt != playerBullet.end()){
            if((*bulletIt)->collidesWithItem(*enemyIt)){
                //碰撞，删除子弹
                Bullet* delBullet = *bulletIt;
                //从场景中移除
                this->removeItem(*bulletIt);
                //从飞机的子弹容器中移除
                bulletIt = playerBullet.erase(bulletIt);
                //释放内存
                delete delBullet;
                //敌机hp下降
                (*enemyIt)->setHp((*enemyIt)->getHp()-(*bulletIt)->getDamage());
                //qDebug() << (*enemyIt)->getHp();
                //播放音效
                damageSound->play();
            }
            else{
                bulletIt++;
            }
        }
        //如果飞机hp下降为0，清除飞机，增加得分
        if((*enemyIt)->getHp() <= 0){
            //判断是否携带灵力
            if((*enemyIt)->isWithPower()){
                Power* newPower = new Power();
                newPower->setPixmap(QPixmap(":/images/resources/power.png").scaled(17,17,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                //qDebug() << (*enemyIt)->pos();
                newPower->setPos((*enemyIt)->pos());
                this->power.append(newPower);
                this->addItem(newPower);
            }
            //保存对象
            EnemyPlane* delEnemy = *enemyIt;
            //从场景中移除
            this->removeItem(*enemyIt);
            //从敌机容器中移除
            enemyIt = enemyPlane.erase(enemyIt);
            //释放内存
            delete delEnemy;
            //加分
            playerPlane->addScore(100);
            //播放音效
            breakSound->play();

        }
        else{
            enemyIt++;
        }
    }

    //检测碰撞(自机与敌机子弹)
    for(auto bulletIt = enemyBullet.begin();bulletIt != enemyBullet.end();bulletIt++){
        //碰撞，先判定是否在无敌，否则减一条命，进入无敌
        if((*bulletIt)->collidesWithItem(playerPlane->getRealCenter())){
            if(!playerPlane->isUnmatched()){
                playerPlane->lossALife();
                playerPlane->setUnmatched(true);
                this->removeItem(lifePixmap.back());
                delete lifePixmap.back();
                lifePixmap.pop_back();
                playerDeadSound->play();

                if(playerPlane->getLife()<=0){
                    isUpdate = false;
                    this->removeItem(playerPlane);
                    this->removeItem(playerPlane->getCenter());
                    this->removeItem(playerPlane->getRealCenter());
                    this->addItem(gameover);
                }
            }
        }
        //擦弹，只播放音效
        if((*bulletIt)->collidesWithItem(playerPlane)){
            grazeSound->play();
        }
    }


    //更新得分
    QString st = QString::number(playerPlane->getScore());
    for(int i=14;i>st.length();i--){
        st = "0"+st;
    }
    scoreText->setPlainText(st);


    //一波敌人打完后，生成新波次，一波没打完之前不生成下一波
    if(enemyPlane.isEmpty()){
        waveCount++;
        //这里我搞成循环了。防止崩掉
        if(waveCount == waveLst.length()){
            waveCount = 1;
        }
        QVector<EnemyPlane*> newEnemy = waveLst[waveCount]();
        for(auto enemyIt = newEnemy.begin();enemyIt != newEnemy.end();enemyIt++){
            this->addItem(*enemyIt);
            enemyPlane.append(*enemyIt);
        }
    }

}

//按下键盘
void GameScene::keyPressEvent(QKeyEvent* event){
    switch (event->key()) {
    case Qt::Key_W:
        playerPlane->setUp(true);
        break;
    case Qt::Key_S:
        playerPlane->setDown(true);
        break;
    case Qt::Key_A:
        playerPlane->setLeft(true);
        break;
    case Qt::Key_D:
        playerPlane->setRight(true);
        break;
    case Qt::Key_J:
        playerPlane->setShoot(true);
        break;
    case Qt::Key_Shift:
        playerPlane->setShift(true);
        playerPlane->setSpeed(2,2);
        break;
    case Qt::Key_R:                 //重新开始
        if(!isUpdate){
            playerPlane->setLife(3);
            playerPlane->setPower(1.00);
            playerPlane->setShift(false);
            playerPlane->setDown(false);
            playerPlane->setLeft(false);
            playerPlane->setUp(false);
            playerPlane->setRight(false);
            playerPlane->setUnmatched(false);
            playerPlane->setPos(240,550);
            playerPlane->getCenter()->setPos(256,578);
            playerPlane->getRealCenter()->setPos(256.5,578.5);
            //残机
            for(int i=0;i<playerPlane->getLife();i++){
                QGraphicsPixmapItem* life = new QGraphicsPixmapItem();
                life->setPixmap(QPixmap(":/images/resources/life.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                life->setPos(650+30*i,180);
                life->setZValue(4);
                lifePixmap.append(life);
                this->addItem(life);
            }
            //得分
            playerPlane->setScore(0);
            QString st = QString::number(playerPlane->getScore());
            for(int i=13;i>st.length();i--){
                st = "0"+st;
            }
            scoreText->setPlainText(st);
            //灵力
            playerPlane->setPower(1.00);
            QString pt = QString::number(playerPlane->getPower(),'f',2);
            powerText->setPlainText(pt);

            this->addItem(playerPlane);
            this->addItem(playerPlane->getCenter());
            this->addItem(playerPlane->getRealCenter());
            isUpdate = true;
            this->removeItem(gameover);
            //给无敌
            playerPlane->setUnmatched(true);
            playerPlane->setUnmatchedCD(120);

        }
        break;
    }  
};


//松开键盘
void GameScene::keyReleaseEvent(QKeyEvent* event){
    switch (event->key()) {
    case Qt::Key_W:
        playerPlane->setUp(false);
        break;
    case Qt::Key_S:
        playerPlane->setDown(false);
        break;
    case Qt::Key_A:
        playerPlane->setLeft(false);
        break;
    case Qt::Key_D:
        playerPlane->setRight(false);
        break;
    case Qt::Key_J:
        playerPlane->setShoot(false);
        break;
    case Qt::Key_Shift:
        playerPlane->setShift(false);
        playerPlane->setSpeed(4,4);
        break;
    }


};



