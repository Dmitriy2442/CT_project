#ifndef ARENA_H
#define ARENA_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsDropShadowEffect>
#include <QVector>
#include <QRectF>

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
    QVector<QRectF> getPlatforms();

private:
    void addPlatform(qreal x, qreal y, qreal width, qreal height);

    QVector<QRectF> platforms;
    QGraphicsPixmapItem *background;
};

#endif // ARENA_H
