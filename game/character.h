#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(QString imagePath, QRectF hitbox = QRectF(0, 0, 100, 100), QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void jump();
    void moveLeft();
    void moveRight();
    void attack();
    void block();

    int getHealth() const;
    void setHealth(int value);

protected:
    QRectF hitbox;

    int health = 100;
    int speed = 5;
    int maxSpeed = 20;
    int jumpHeight;
    int attackDamage;
};

#endif // CHARACTER_H
