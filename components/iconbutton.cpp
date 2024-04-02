#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton{parent}
{
    setText("");
    setFixedSize(128, 128);

    setStyleSheet("QPushButton {"
                  "border: none;" // Убираем границу
                  "background-color: transparent;" // Делаем фон прозрачным
                  "background-image: url(:/assets/icons/amogus.png);" // Указываем путь к изображению
                  "background-position: center;" // Размещение изображения по центру
                  "background-repeat: no-repeat;" // Отключаем повторение изображения
                  "}");

    connect(this, &QPushButton::clicked, this, &IconButton::onButtonClicked);
}

void IconButton::changeBackgroundImage(const QString &imagePath) {
    QString styleSheet = QString("QPushButton {"
                                 "border: none;"
                                 "background-color: transparent;"
                                 "background-image: url(%1);"
                                 "background-position: center;"
                                 "background-repeat: no-repeat;"
                                 "}").arg(imagePath);
    setStyleSheet(styleSheet);
}

void IconButton::onButtonClicked() {
    // Логика, выполняемая при нажатии на кнопку
    qDebug() << "Кнопка нажата!";
}
