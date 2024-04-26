#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QtGlobal>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(QString imagePath, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF calculateHitbox(const QImage &image);

    void updateState();
    void updateImage();

    void jump();
    void moveLeft();
    void moveRight();
    void attack();
    void block();

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
    int speed = 5;
    int maxSpeed = 20;
    int jumpHeight;
    int attackDamage;
};

#endif // CHARACTER_H
