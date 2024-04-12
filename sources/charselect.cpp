#include "headers/charselect.h"
#include "../ui/ui_charselect.h"

CharSelect::CharSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharSelect)
{
    ui->setupUi(this);
    ui->readyOverlay->hide();
    dotTimer = new QTimer(this);
    connect(dotTimer, &QTimer::timeout, this, &CharSelect::updateDots);
    connect(ui->backIcon, &QPushButton::clicked, this, &CharSelect::on_backIcon_clicked);
    connect(this, &CharSelect::playersChose, this, &CharSelect::readyCheck);
    connect(ui->noButton, &QPushButton::clicked, this, &CharSelect::setUpClear);
    connect(ui->yesButton, &QPushButton::clicked, this, &CharSelect::beginGame);

    // TODO Здесь должен быть запрос в базу данных
    QVector<QString> names {"Skipper", "Rico", "Literally me"};
    QVector<QString> imagePaths {":/testchars/skipper.png", ":/testchars/rico.png", ":/testchars/peng.png"};
    for (int i = 0; i < names.size(); ++i) {
        QString name = names.at(i);
        QString imagePath = imagePaths.at(i);

        CharacterCard* card = new CharacterCard(name, imagePath);
        ui->cardLayout->addWidget(card);
        connect(card, &CharacterCard::cardClicked, this, &CharSelect::handleCardClick);
    }
}

void CharSelect::setUpClear()
{
    dotTimer->start(700);
    choosingPlayer = 1;
    ui->readyOverlay->hide();
}

void CharSelect::updateDots()
{
    QString dots = QString(".").repeated(dotCount);
    baseText = QStringLiteral("Player %1 is choosing").arg(choosingPlayer);
    ui->choosingLabel->setText(baseText + dots);
    dotCount = (dotCount % 3) + 1;
}

void CharSelect::handleCardClick(const QString &name) {
    switch(choosingPlayer)
    {
    case 1:
        name1 = name;
        choosingPlayer = 2;
        break;
    case 2:
        name2 = name;
        emit playersChose(name1, name2);
        qDebug() << "Character selection complete: "<< name1 << " and " << name2;
    }
}

void CharSelect::readyCheck() {
    ui->readyOverlay->show();
}

CharSelect::~CharSelect()
{
    delete ui;
}

