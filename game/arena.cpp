#include "Arena.h"

Platform::Platform(int x, int y, int width, int height, QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    // Создаем QPainterPath с скругленными углами
    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, width, height), 10.0, 10.0); // радиус скругления 10 пикселей
    setPath(path);

    // Перемещаем элемент на требуемую позицию
    setPos(x, y);

    // Стиль заливки и границы
    QPen pen(Qt::black, 1);  // Черная граница толщиной 1 пиксель
    QBrush brush(Qt::gray); // Серый цвет заливки
    setPen(pen);
    setBrush(brush);


    // Добавление тени
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setOffset(5, 5);
    setGraphicsEffect(effect);
}



Arena::Arena(QObject *parent) : QGraphicsScene(parent), background(nullptr),
    xOffset(0),
    speed(1)
{
    background.load(":/images/background.jpg");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Arena::updateBackground);
    timer->start(30); // обновление каждые 30 мс
}

void Arena::updateBackground() {
    xOffset += speed;
    if (xOffset > background.width()) {
        xOffset -= background.width();
    }
    invalidate(); // Перерисовать сцену
}

void Arena::drawBackground(QPainter* painter, const QRectF& rect) {
    QRectF source(xOffset, 0, background.width() - xOffset, background.height());
    QRectF target(0, 0, background.width() - xOffset, background.height());
    painter->drawImage(target, background, source);

    if (xOffset > 0) {
        QRectF source2(0, 0, xOffset, background.height());
        QRectF target2(background.width() - xOffset, 0, xOffset, background.height());
        painter->drawImage(target2, background, source2);
    }
}

void Arena::setupArena(const QSize size) {
    setSceneRect(0, 0, size.width(), size.height());

    // Добавление фонового изображения
    //QPixmap bgPixmap(":/images/background.jpg");

    // Добавление платформ
    addPlatform(100, 600, 1080, 20); // Главная платформа
    addPlatform(515, 200, 250, 20); // Верхняя платформа
    addPlatform(200, 400, 250, 20); // Левая платформа
    addPlatform(830, 400, 250, 20); // Правая платформа
}

QVector<QRectF> Arena::getPlatforms() {
    return platforms;
}

QPair<qreal, qreal> Arena::initPos1() {
    return QPair<qreal, qreal>(0, 340);
}
QPair<qreal, qreal> Arena::initPos2() {
    return QPair<qreal, qreal>(879, 340);
}

void Arena::addPlatform(qreal x, qreal y, qreal width, qreal height) {
    Platform *platform = new Platform(x, y, width, height);
    addItem(platform);
    QRectF hitbox(x, y, width, height);
    platforms.push_back(hitbox);
}
