#include "headers/charselect.h"
#include "../ui/ui_charselect.h"

CharSelect::CharSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharSelect)
{
    ui->setupUi(this);
    dotTimer = new QTimer(this);
    connect(dotTimer, &QTimer::timeout, this, &CharSelect::updateDots);
    connect(ui->backIcon, &QPushButton::clicked, this, &CharSelect::on_backIcon_clicked);
    dotTimer->start(1000);

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

void CharSelect::updateDots()
{
    QString dots = QString(".").repeated(dotCount);
    ui->choiceLabel->setText(baseText + dots);
    dotCount = (dotCount % 3) + 1;
}

void CharSelect::playerOneChoosing() {
    baseText = "Player 1 is choosing";
    dotCount = 1;
    ui->choiceLabel->setText(baseText + ".");
}

void CharSelect::playerTwoChoosing() {
    baseText = "Player 2 is choosing";
    dotCount = 1;
    ui->choiceLabel->setText(baseText + ".");
}

CharSelect::~CharSelect()
{
    delete ui;
}

