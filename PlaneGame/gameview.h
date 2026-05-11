#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gamescene.h"
#include <QGraphicsView>
#include <QKeyEvent>

class GameView : public QGraphicsView
{
public:
    GameView();
    GameView(GameScene* scene,QWidget *parent);
};

#endif // GAMEVIEW_H
