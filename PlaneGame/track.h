#ifndef TRACK_H
#define TRACK_H

#include <QPointF>

class Track
{
public:
    Track();
    static int randInt(int a,int b);

    //预设轨迹
    static QPointF x_linearTrack(int t);
    static QPointF y_linearTrack(int t);
    static QPointF linearTrack(int t);
    static QPointF circleTrack(int t);
    static QPointF y_linear_stopTrack(int t);
    static QPointF randomTrack(int t);
};

#endif // TRACK_H
