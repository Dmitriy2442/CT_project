#include "charactercard.h"

CharacterCard::CharacterCard(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "Character card initialized without name and image path";
}

CharacterCard::CharacterCard(const QString &name, const QString &imagePath, QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создание и настройка QLabel для картинки
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(imagePath).scaled(100, 100)); // Установка пути к картинке
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);


    // Создание QLabel для текста
    QLabel *textLabel = new QLabel(name, this);
    textLabel->setStyleSheet("QLabel { color : white; font-size: 32px;}");
    textLabel->setAlignment(Qt::AlignCenter);

    // Создание и применение эффекта прозрачности к тексту
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1.0);
    textLabel->setGraphicsEffect(opacityEffect);

    layout->addWidget(textLabel);

    // Настройка виджета
    setLayout(layout);
}
