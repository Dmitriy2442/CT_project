#include "Character.h"

Character::Character(QString imagePath, QRectF hitbox, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    hitbox(hitbox) {
    if (imagePath != "")
        setPixmap(QPixmap(imagePath).scaled(hitbox.width(), hitbox.height())); // Устанавливаем изображение персонажа
    else
        setPixmap(QPixmap(":testchars/skipper.png").scaled(hitbox.width(), hitbox.height())); // Дефолтное изображение
    setZValue(1); // Устанавливаем слой отрисовки
}

QRectF Character::boundingRect() const {
    return hitbox; // Возвращаем хитбокс персонажа
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);  // Рисуем изображение персонажа
    painter->setPen(Qt::red);  // Устанавливаем красный цвет для хитбокса
    painter->drawRect(hitbox);  // Рисуем хитбокс вокруг персонажа
}

void Character::accLeft() {
    if (speedX > (-1) * maxSpeedX)
        speedX = speedX - accelerationX;
}

void Character::accRight() {
    if (speedX < maxSpeedX)
        speedX = speedX + accelerationX;
}

void Character::jump() {    // Реализация прыжка
    if (1)          //TODO: флаг нижней коллизии
        speedY = (-1) * jumpSpeed;
}

void Character::attack() {
    // Реализация атаки
    // Это может включать изменение изображения на анимацию атаки и проверку попадания
}

void Character::block() {
    // Реализация блокирования
    // Это может включать изменение изображения на анимацию блокирования и уменьшение получаемого урона
}

void Character::movement() {
    setPos(x() + speedX, y() + speedY);
    if (speedX < 0)
        speedX++;
    else if (speedX > 0)
        speedX--;

    if (speedY < maxSpeedY)
        speedY += gravAcc;
}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int value) {
    health = value;
    if (health <= 0) {
        // Обработка смерти персонажа, возможно, отправка сигнала
    }
}
