#include "headers/charselect.h"
#include "../ui/ui_charselect.h"

CharSelect::CharSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharSelect)
{
    ui->setupUi(this);
    connect(ui->backIcon, &QPushButton::clicked, this, &CharSelect::on_backIcon_clicked);

    QVector<QString> names {"Skipper", "Rico", "Literally me"};
    QVector<QString> imagePaths {":/testchars/skipper.png", ":/testchars/rico.png", ":/testchars/peng.png"};
    // Здесь должен быть запрос в базу данных
    for (int i = 0; i < names.size(); ++i) {
        QString name = names.at(i);
        QString imagePath = imagePaths.at(i);

        CharacterCard* card = new CharacterCard(name, imagePath);
        ui->cardLayout->addWidget(card);
    }
}

CharSelect::~CharSelect()
{
    delete ui;
}

