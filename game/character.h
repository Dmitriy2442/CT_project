#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QtGlobal>
#include <QTransform>
#include <QVector>
#include <QRectF>
#include <QPair>

#include <QtMath>

struct attackZone {
    QRectF hitbox;
    int attackPower;
};

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(int char_id, QString imagePath, QVector<QRectF> arena_platforms, QVector<attackZone> *attackZonesVec, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF calculateHitbox(const QImage &image);

    void updateState();
    void updateImage();

    void fixPosition(); // Костыль метод

    void deathConditions();
    void jump();
    void accLeft();
    void accRight();
    void attack();
    void block(bool value);
    void acceleration();

    int checkCollision();
    bool standingCondition();
    void movement();
    void attackUpdate();

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

    int id;
    int health = 300;

signals:
    void death(int id);


protected:
    QRectF hitbox;
    QSize imageScale = {2, 2};
    QMap<QString, QPixmap> stateImages;

    QString currentState = "Standing";
    int frameUpdateRate = 5;
    int attackFrames = 15;
    int attackCooldown = 15;
    int attackCooldownCounter = 0;
    int runFrames = 7;
    int currentFrame = 0;

    int blockRadius = 25; // Default value, assigned dynamically in constructor

    short lookDirection = 1;
    bool isBlocking = false;
    qreal accelerationX = 2;
    qreal acceleartionY = -2;
    qreal speedX = 0;
    qreal speedY = 0;
    int maxSpeedX = 20;
    int maxSpeedY = 20;
    int jumpSpeed = 20;
    qreal gravAcc = 0.6;
    int attackDamage;

    QVector<QRectF> platforms;
    QVector<attackZone> *attackZones;
};

#endif // CHARACTER_H
