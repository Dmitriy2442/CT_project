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

void Character::moveLeft() {
    setPos(x() - speed, y()); // Плохая логика движения влево
}

void Character::moveRight() {
    setPos(x() + speed, y()); // Плохая логика движения вправо
}

void Character::jump() {
    // Реализация прыжка
}

void Character::attack() {
    // Реализация атаки
    // Это может включать изменение изображения на анимацию атаки и проверку попадания
}

void Character::block() {
    // Реализация блокирования
    // Это может включать изменение изображения на анимацию блокирования и уменьшение получаемого урона
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
