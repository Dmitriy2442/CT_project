#include "charactercard.h"

CharacterCard::CharacterCard(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "Character card initialized without name and image path";
}

CharacterCard::CharacterCard(const QString &name, const QString &imagePath, QWidget *parent)
    : name(name)
    , imagePath(imagePath)
    , QWidget{parent}
{
    setMouseTracking(true);
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создание и настройка QLabel для картинки
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(imagePath).scaled(100, 100));
    imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    layout->addWidget(imageLabel);

    // Создание QLabel для текста
    QLabel *textLabel = new QLabel(name, this);
    textLabel->setAttribute(Qt::WA_TranslucentBackground);
    textLabel->setStyleSheet("QLabel { color : white; font-size: 32px;}");
    textLabel->setAlignment(Qt::AlignCenter);

    // Создание и применение эффекта прозрачности к тексту
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1.0);
    textLabel->setGraphicsEffect(opacityEffect);

    // Добавление текстового QLabel поверх изображения
    auto *overlayLayout = new QVBoxLayout(imageLabel);
    overlayLayout->addWidget(textLabel, 0, Qt::AlignBottom | Qt::AlignCenter);

    // Настройка виджета
    setLayout(layout);
}

void CharacterCard::resetCard()
{
    hover = false;
    fixColor = false;
    blocked = false;
    update();
}

void CharacterCard::fixCard(const QString &color)
{
    this->color = color;
    fixColor = true;
    blocked = true;

    update();
}

bool CharacterCard::isBlocked()
{
    return blocked;
}

void CharacterCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit cardClicked(name);
}

void CharacterCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::white, 3);
    if (fixColor) {
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
    } else if (hover) {
        pen.setColor(Qt::white);
        pen.setStyle(Qt::SolidLine);
    } else {
        pen.setStyle(Qt::NoPen);
    }
    painter.setPen(pen);
    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 10, 10);
}

void CharacterCard::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event)
    hover = true;
    update();
}

void CharacterCard::leaveEvent(QEvent *event) {
    Q_UNUSED(event)
    hover = false;
    update();
}
