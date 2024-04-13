#include "headers/charselect.h"
#include "../ui/ui_charselect.h"

CharSelect::CharSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharSelect)
{
    ui->setupUi(this);
    ui->readyOverlay->hide();
    dotTimer = new QTimer(this);
    selectionTimer = new QTimer(this);
    selectionTimer->setSingleShot(true);
    selectionTimer->setInterval(1000);
    connect(dotTimer, &QTimer::timeout, this, &CharSelect::updateDots);
    connect(selectionTimer, &QTimer::timeout, this, &CharSelect::handleSelectionDelay);

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
        connect(this, &CharSelect::resetAllCards, card, &CharacterCard::resetCard);
    }
}

void CharSelect::setUpClear()
{
    dotTimer->start(700);
    choosingPlayer = 1;
    ui->readyOverlay->hide();
    emit resetAllCards();
    update();
}

void CharSelect::updateDots()
{
    QString dots = QString(".").repeated(dotCount);
    baseText = QStringLiteral("Player %1 is choosing").arg(choosingPlayer);
    ui->choosingLabel->setText(baseText + dots);
    dotCount = (dotCount % 3) + 1;
}

void CharSelect::handleCardClick(const QString &name) {
    CharacterCard* card = qobject_cast<CharacterCard*>(sender());
    if (!card->isBlocked())
    {
        card->fixCard(player2color[choosingPlayer]);
        switch(choosingPlayer)
        {
        case 1:
            name1 = name;
            choosingPlayer++;
            break;
        case 2:
            name2 = name;
            dotTimer->stop();
            selectionTimer->start();
            break;
        }
    }
}

void CharSelect::handleSelectionDelay() {
    emit playersChose(name1, name2);
}

void CharSelect::readyCheck() {
    ui->readyOverlay->show();
}

CharSelect::~CharSelect()
{
    delete ui;
}

