#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton{parent}
{
    setText("Test text");

    connect(this, &QPushButton::clicked, this, &IconButton::onButtonClicked);
}

void IconButton::onButtonClicked() {
    // Логика, выполняемая при нажатии на кнопку
    qDebug() << "Кнопка нажата!";
}
