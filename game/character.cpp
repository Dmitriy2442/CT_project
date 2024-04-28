#include "game/character.h"


Character::Character(QString imagePath, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    for (int i = 0; i < State.size(); ++i) {
        stateImages[State[i]] = QPixmap(imagePath + "/" + State[i] + ".png");
    }

    QPixmap basePixmap = stateImages["Standing"];
    basePixmap = basePixmap.scaled(basePixmap.width()*imageScale.width(), basePixmap.height()*imageScale.height());
    setPixmap(basePixmap);

    hitbox = calculateHitbox(pixmap().toImage());

    blockRadius = qMax(hitbox.width(), hitbox.height()) / 2 + 5;

    setZValue(1); // Устанавливаем слой отрисовки
}


void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);  // Рисуем изображение персонажа
    painter->setPen(Qt::red);  // Устанавливаем красный цвет для хитбокса
    painter->drawRect(hitbox);  // Рисуем хитбокс вокруг персонажа

    if (currentState == "Blocking") {
        painter->setPen(QPen(Qt::red, 3));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(hitbox.center(), blockRadius, blockRadius);
    }
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
    if (currentState == "Attacking" && currentFrame < attackFrames) {
        ++currentFrame;
        return;
    } else if (currentState == "Attacking" && currentFrame == attackFrames) {
        currentFrame = 0;
        attackCooldownCounter = attackCooldown;
        currentState = "Standing";
    }
    attackCooldownCounter = qMax(0, attackCooldownCounter - 1);

    if (speedY > 0) {
        currentState = "Falling";
        return;
    }

    if (speedY < 0) {
        currentState = "Jumping";
        return;
    }

    if (speedX != 0) {
        if (currentState != "Running1" && currentState != "Running2") {
            currentState = "Running1";
            currentFrame = 0;
        } else if (currentFrame < runFrames) {
            ++currentFrame;
        } else {
            currentFrame = 0;
            currentState = (currentState == "Running1") ? "Running2" : "Running1";
        }
        return;
    }

    if (isBlocking) {
        currentState = "Blocking";
        return;
    }

    currentState = "Standing";
}

void Character::updateImage() {
    updateState();

    QTransform transform;
    transform.scale(lookDirection, 1);

    QPixmap image = stateImages[currentState].transformed(transform);
    image = image.scaled(image.width()*imageScale.width(), image.height()*imageScale.height());
    setPixmap(image);

    if (currentState != "Attacking") {
        hitbox = calculateHitbox(image.toImage());
    }
}

void Character::fixPosition() {
    // Функция проверяет hitbox и сдвигает его, если он выходит за границы экранаq
    if (x() + hitbox.x() < 0) {
        setPos(0 - hitbox.x(), y());
    } else if (x() + hitbox.x() + hitbox.width() > 1280) {
        setPos(1280 - hitbox.width() - hitbox.x(), y());
    }
    if (y() + hitbox.y() < 0) {
        setPos(x(), 0 - hitbox.y());
    } else if (y() + hitbox.y() + hitbox.height() > 720) {
        setPos(x(), 720 - hitbox.height() - hitbox.y());
    }
}

void Character::accLeft() {
    lookDirection = -1;
    if (speedX > (-1) * maxSpeedX)
        speedX = speedX - accelerationX;
}

void Character::accRight() {
    lookDirection = 1;
    if (speedX < maxSpeedX)
        speedX = speedX + accelerationX;
}

void Character::jump() {    // Реализация прыжка
    if (1)          //TODO: флаг нижней коллизии
        speedY = (-1) * jumpSpeed;
}

void Character::attack() {
    if (attackCooldownCounter > 0 || currentState == "Attacking") {
        return;
    }
    currentState = "Attacking";
    currentFrame = 0;
    // Реализация атаки
    // Это может включать изменение изображения на анимацию атаки и проверку попадания
}

void Character::block(bool value) {
    this->isBlocking = value;
    if (value) {
        // Реализация блокирования
        // Это может включать изменение изображения на анимацию блокирования и уменьшение получаемого урона
    }
}

void Character::acceleration() {
    setPos(x() + speedX, y() + speedY);
    if (speedX < 0)
        speedX++;
    else if (speedX > 0)
        speedX--;

    if (speedY < maxSpeedY) {
        // speedY += gravAcc;
    }
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
