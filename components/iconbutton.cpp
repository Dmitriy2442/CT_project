#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton{parent}
{
    setText("Test text");
    setFixedSize(128, 128);

    setStyleSheet("QPushButton {"
                  "border: none;" // Убираем границу
                  "background-color: transparent;" // Делаем фон прозрачным
                  "background-image: url(:/assets/icons/gear.png);" // Указываем путь к изображению
                  "background-position: center;" // Размещение изображения по центру
                  "background-repeat: no-repeat;" // Отключаем повторение изображения
                  "}");

    connect(this, &QPushButton::clicked, this, &IconButton::onButtonClicked);
}

void IconButton::onButtonClicked() {
    // Логика, выполняемая при нажатии на кнопку
    qDebug() << "Кнопка нажата!";
}
