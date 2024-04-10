#include "../headers/charselect.h"
#include "../ui/ui_charselect.h"

CharSelect::CharSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharSelect)
{
    ui->setupUi(this);
    connect(ui->backIcon, &QPushButton::clicked, this, &CharSelect::on_backIcon_clicked);
}

CharSelect::~CharSelect()
{
    delete ui;
}

