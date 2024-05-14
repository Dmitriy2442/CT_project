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
#include <QPainter>
#include <QPair>
#include <QTimer>

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

    void updateBackground();

    QVector<QRectF> getPlatforms();
    QPair<qreal, qreal> initPos1();
    QPair<qreal, qreal> initPos2();

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    void addPlatform(qreal x, qreal y, qreal width, qreal height);

    QVector<QRectF> platforms;

    QImage background;
    QTimer *timer;
    int xOffset;
    int speed;
};

#endif // ARENA_H
