#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton{parent}
{
    setText("");
    setFixedSize(80, 80);

    setStyleSheet("QPushButton {"
                  "border: none;" // Убираем границу
                  "background-color: transparent;" // Делаем фон прозрачным
                  "border-image: url(:/assets/icons/amogus.png) 0 0 0 0 stretch stretch;" // Указываем путь к изображению
                  "border-width: 0px;"
                  "background-position: center;" // Размещение изображения по центру
                  "background-repeat: no-repeat;" // Отключаем повторение изображения
                  "}");

    connect(this, &QPushButton::clicked, this, &IconButton::onButtonClicked);
}

void IconButton::changeBackgroundImage(const QString &imagePath) {
    QString styleSheet = QString("QPushButton {"
                                 "border: none;"
                                 "background-color: transparent;"
                                 "border-image: url(%1) 0 0 0 0 stretch stretch;"
                                 "border-width: 0px;"
                                 "background-position: center;"
                                 "background-repeat: no-repeat;"
                                 "}").arg(imagePath);
    setStyleSheet(styleSheet);
}

void IconButton::onButtonClicked() {
    // Логика, выполняемая при нажатии на кнопку
    qDebug() << "Кнопка нажата!";
}
