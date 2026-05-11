#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QSoundEffect>

class Background : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void stream();

public:
    explicit Background(QObject *parent = nullptr);

private:
    QSoundEffect* bgm;

signals:
};

#endif // BACKGROUND_H
