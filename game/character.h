#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QtGlobal>
#include <QVector>
#include <QRectF>
#include <QPair>

#include <QtMath>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(QString imagePath, QVector<QRectF> arena_platforms, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF calculateHitbox(const QImage &image);

    void updateState();
    void updateImage();

    void jump();
    void accLeft();
    void accRight();
    void attack();
    void block();
    void acceleration();

    int checkCollision();
    void movement();

    int getHealth() const;
    void setHealth(int value);

    QVector<QString> State {
        "Attacking",
        "Falling",
        "Jumping",
        "Running1",
        "Running2",
        "Blocking",
        "Standing"
    };


protected:

    QRectF hitbox;
    QSize imageScale = {2, 2};
    QMap<QString, QPixmap> stateImages;

    QString currentState = "Standing";
    int frameUpdateRate = 5;
    int attackFrames = 30;
    int currentAttackFrame = 0;

    int health = 100;
    qreal accelerationX = 2;
    qreal acceleartionY = -2;
    qreal speedX = 0;
    qreal speedY = 0;
    int maxSpeedX = 20;
    int maxSpeedY = 20;
    int jumpSpeed = 10;
    int gravAcc = 1;
    int attackDamage;

    QVector<QRectF> platforms;
};

#endif // CHARACTER_H
