#include "headers/game.h"
#include "../ui/ui_game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    connect(ui->debugButton, &QPushButton::clicked, this, &Game::on_debugButton_clicked);
}

Game::~Game()
{
    delete ui;
}
