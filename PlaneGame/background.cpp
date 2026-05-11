#include "background.h"
#include <QGraphicsPixmapItem>
#include <QUrl>

Background::Background(QObject *parent)
    : QObject{parent}
{
    bgm = new QSoundEffect(this);
    bgm->setSource(QUrl::fromLocalFile(":/sounds/resources/bgm.wav"));
    bgm->setLoopCount(30);
    bgm->play();
}


void Background::stream(){
    if(this->y() >= 0){
        this->setPos(0,-700+2);
    }
    else{
        this->moveBy(0,2);
    }
}
