#include "gameview.h"

GameView::GameView() {}

GameView::GameView(GameScene* scene,QWidget *parent)
    :QGraphicsView(scene,parent)
{

}
