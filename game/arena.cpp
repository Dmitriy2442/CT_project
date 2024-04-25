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



Arena::Arena(QObject *parent) : QGraphicsScene(parent), background(nullptr) {
    // Инициализация сцены может быть выполнена здесь
}

void Arena::setupArena(const QSize size) {
    setSceneRect(0, 0, size.width(), size.height());

    // Добавление фонового изображения
    QPixmap bgPixmap(":/images/background.jpg");
    background = addPixmap(bgPixmap);
    background->setZValue(-1);

    // Добавление платформ
    addPlatform(50, 600, 1000, 30);
    addPlatform(500, 150, 250, 20);
}

void Arena::addPlatform(qreal x, qreal y, qreal width, qreal height) {
    Platform *platform = new Platform(x, y, width, height);
    addItem(platform);
}
