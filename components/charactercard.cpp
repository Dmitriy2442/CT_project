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
