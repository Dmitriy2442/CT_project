#include "game/character.h"

Character::Character(int char_id, QString imagePath, QVector<QRectF> arena_platforms, QVector<attackZone> *attackZonesVec, QGraphicsItem *parent) :
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

    platforms = arena_platforms;
    attackZones = attackZonesVec;
    id = char_id;
}


void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);  // Рисуем изображение персонажа
    painter->setPen(Qt::red);  // Устанавливаем красный цвет для хитбокса
    painter->drawRect(hitbox);  // Рисуем хитбокс вокруг персонажа
    if (currentState == "Attacking") {
        painter->drawRect((*attackZones)[id].hitbox);   //Хитбокс атаки
        qDebug() << (*attackZones)[id].hitbox;
    }

    painter->drawRect(boundingRect());

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
        (*attackZones)[id].hitbox = QRectF();
        (*attackZones)[id].attackPower = 0;
    }
    attackCooldownCounter = qMax(0, attackCooldownCounter - 1);

    if (speedY > 2) {
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

void Character::deathConditions() {
    if ((x() + hitbox.x() < -500) || (x() + hitbox.x() + hitbox.width() > 1780) || (y() + hitbox.y() < -500) || (y() + hitbox.y() + hitbox.height() > 1220)) {
        health -= 100; // менять здоровье перса
        setPos(640 - hitbox.x() - hitbox.width()/2, 200);
        speedX = 0;
        speedY = 0;

        if (health <= 0)
            emit death(id);
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
    if (standingCondition())
        speedY = (-1) * jumpSpeed;
}

void Character::attack() {
    if (attackCooldownCounter > 0 || currentState == "Attacking") {
        return;
    }

    currentState = "Attacking";
    currentFrame = 0;
    attackZone charAttackZone;
    charAttackZone.attackPower = attackDamage * lookDirection;
    charAttackZone.hitbox = QRectF(x() + hitbox.x() + hitbox.width()/2 + lookDirection * 70 + (lookDirection - 1)/2*50, y() + hitbox.y() + hitbox.height()/2 - 25, 50, 50);
    (*attackZones)[id] = charAttackZone;
}

void Character::block(bool value) {
    this->isBlocking = value;
    if (value) {
        // Реализация блокирования
        // Это может включать изменение изображения на анимацию блокирования и уменьшение получаемого урона
    }
}

void Character::acceleration() {
    if (speedX < 0)
        speedX++;
    else if (speedX > 0)
        speedX--;

    if ((speedY < maxSpeedY) && (!standingCondition())) {
         speedY += gravAcc;
    }
}

int Character::checkCollision() {
    for (int i = 0; i < platforms.size(); i++) {
        QRectF current_hitbox(x()+hitbox.x(), y()+hitbox.y(), hitbox.width(), hitbox.height());
        if (current_hitbox.intersects(platforms[i])) {
            return i;
        }
    }
    return -1;
}

bool Character::standingCondition() {
    setPos(x(), y() + 1);
    if (checkCollision() > -1) {
        setPos(x(), y() - 1);
        return 1;
    }
    else
        return 0;
}

void Character::movement() {
    qreal varSpeedX, varSpeedY;
    // qDebug() << x() << y();
    varSpeedX = speedX;
    varSpeedY = speedY;

    setPos(x() + varSpeedX, y());
    if (checkCollision() > -1) {
        setPos(x() - varSpeedX, y());
        varSpeedX = 0;
    }
    setPos(x(), y() + varSpeedY);
    if (checkCollision() > -1) {
        setPos(x(), y() - varSpeedY);
        varSpeedY = 0;
    }
    speedX = varSpeedX;
    speedY = varSpeedY;

    //Pos correction in case of getting stuck in the platform
    while (checkCollision() > -1)
        setPos(x(), y() - 1);
}

void Character::attackUpdate() {
    QRectF current_hitbox(x()+hitbox.x(), y()+hitbox.y(), hitbox.width(), hitbox.height());
    if (current_hitbox.intersects((*attackZones)[!id].hitbox))
        return;   //Место для функции Кирпича
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
