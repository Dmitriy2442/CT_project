#include "game/character.h"


Character::Character(QString imagePath, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    for (int i = 0; i < State.size(); ++i) {
        stateImages[State[i]] = QPixmap(imagePath + "/" + State[i] + ".png");
    }

    setPixmap(stateImages["Standing"].scaled(stateImages["Standing"].width()*imageScale.width(), stateImages["Standing"].height()*imageScale.height()));

    hitbox = calculateHitbox(pixmap().toImage());

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

QRectF Character::calculateHitbox(const QImage &image) {
    int minX = image.width();
    int maxX = 0;
    int minY = image.height();
    int maxY = 0;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (qAlpha(image.pixel(x, y)) != 0) {  // Проверка на непрозрачность пикселя
                minX = qMin(minX, x);
                maxX = qMax(maxX, x);
                minY = qMin(minY, y);
                maxY = qMax(maxY, y);
            }
        }
    }

    if (minX <= maxX && minY <= maxY) {
        return QRectF(minX, minY, maxX - minX + 1, maxY - minY + 1);
    }
    return QRectF();  // В случае, если все пиксели прозрачные
}

void Character::updateState() {
    if (currentState == "Attacking" && currentAttackFrame < attackFrames) {
        ++currentAttackFrame;
        return;
    } else if (currentState == "Attacking" && currentAttackFrame == attackFrames) {
        currentAttackFrame = 0;
        currentState = "Standing";
    }


}

void Character::updateImage() {
    setPixmap(stateImages[currentState].scaled(stateImages[currentState].width()*imageScale.width(), stateImages[currentState].height()*imageScale.height()));

    hitbox = calculateHitbox(pixmap().toImage());
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

void Character::acceleration() {
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
