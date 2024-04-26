#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>

#include <QtMath>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(QString imagePath, QRectF hitbox = QRectF(0, 0, 100, 100), QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void jump();
    void accLeft();
    void accRight();
    void attack();
    void block();
    void acceleration();

    int getHealth() const;
    void setHealth(int value);

protected:
    QRectF hitbox;

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
};

#endif // CHARACTER_H
