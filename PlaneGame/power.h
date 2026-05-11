#ifndef POWER_H
#define POWER_H

#include <QGraphicsPixmapItem>

class Power:public QGraphicsPixmapItem
{
public:
    Power();

    void move();

private:
    double v = -1.5;
    double a = 0.03;
    //double v = 0;
    //double a = 0;
};

#endif // POWER_H
