#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamescene.h"          //场景，管理所有图形项
#include "gameview.h"           //视图，控制用户视角、焦点
#include <QGraphicsView>        //视图，处理显示
#include <QGraphicsPixmapItem>  //图形项

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GameScene* scene;       //场景
    GameView* view;         //玩家视图

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H
