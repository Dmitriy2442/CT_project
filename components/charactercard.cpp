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
    imageLabel->setPixmap(QPixmap(imagePath)); // Установка пути к картинке
    layout->addWidget(imageLabel);

    // Создание QLabel для текста
    QLabel *textLabel = new QLabel(name, this);
    textLabel->setAlignment(Qt::AlignCenter);

    // Создание и применение эффекта прозрачности к тексту
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.5);
    textLabel->setGraphicsEffect(opacityEffect);

    layout->addWidget(textLabel);

    // Настройка виджета
    setLayout(layout);
    setFixedSize(200, 200);
}
