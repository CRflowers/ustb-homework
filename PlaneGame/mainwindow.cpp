#include "mainwindow.h"
#include <QGraphicsPixmapItem>
#include <Qdebug>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new GameScene(this);       //场景
    scene->setSceneRect(0,0,865,700);

    view = new GameView(scene,this);   //视图
    view->setFixedSize(865,700);
    view->setRenderHint(QPainter::Antialiasing);    //抗锯齿
    view->setRenderHint(QPainter::SmoothPixmapTransform);    //平滑缩放
    //设置视图的边框为0，防止视图与场景大小不匹配
    view->setFrameStyle(0);
    //视图居中显示
    setCentralWidget(view);
    //禁用滚动条
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow() {}


