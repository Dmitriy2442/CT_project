#include "../headers/history.h"
#include "../ui/ui_history.h"

QString createMatchLabel(const QStringList &match) {
    QString color1 = "#ba1012";
    QString color2 = "#1c5ad6";
    QString winnerColor = (match[2] == match[0]) ? color1 : color2;

    QString labelContent = QString("<font color='%1'>%2</font>    vs    <font color='%3'>%4</font> ⟾ Winner: <font color='%5'>%6</font>")
                               .arg(color1)     // цвет первого игрока
                               .arg(match[0])   // имя первого игрока
                               .arg(color2)     // цвет второго игрока
                               .arg(match[1])   // имя второго игрока
                               .arg(winnerColor) // цвет победителя
                               .arg(match[2]);  // имя победителя

    return labelContent;
}

HistoryForm::HistoryForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryForm)
{
    ui->setupUi(this);
}

HistoryForm::HistoryForm(QVector<QVector<QString>> matches, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryForm),
      matches(matches)
{
    ui->setupUi(this);
    updateHistory(matches);

    connect(ui->backIcon, &QPushButton::clicked, this, &HistoryForm::on_backIcon_clicked);
}

void HistoryForm::updateHistory(QVector<QVector<QString>> matches) {
    this->matches = matches;
    updateMatches();
}

void HistoryForm::updateMatches() {
    // Clear matchesLayout before updating
    QLayoutItem *child;
    while ((child = ui->matchesLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (int i = 0; i < 5; i++) {
        QLabel *label = new QLabel();
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 60px; color: #ffffff;");
        if (matches[i][0] != "") {
            label->setText(createMatchLabel(matches[i]));
        }
        ui->matchesLayout->addWidget(label);
    }
    update();
}


HistoryForm::~HistoryForm()
{
    delete ui;
}
