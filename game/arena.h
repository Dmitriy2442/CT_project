#ifndef ARENA_H
#define ARENA_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsDropShadowEffect>

class Platform : public QGraphicsPathItem {
public:
    Platform(int x, int y, int width, int height, QGraphicsItem *parent = nullptr);
};

class Arena : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Arena(QObject *parent = nullptr);
    void setupArena(const QSize size={1280, 720});

private:
    void addPlatform(qreal x, qreal y, qreal width, qreal height);

    QGraphicsPixmapItem *background;
};

#endif // ARENA_H
