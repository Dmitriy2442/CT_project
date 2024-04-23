#include "headers/game.h"

#include "../ui/ui_game.h"
#include "../ui/ui_pausemenu.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this); // Вот эта...
    view = new QGraphicsView(scene, this); // ...и вот эта штуки нужны для отрисовки самой игры

    pauseMenu = new QWidget(this);
    Ui::PauseMenuForm* pauseMenuUi = new Ui::PauseMenuForm();
    pauseMenuUi->setupUi(pauseMenu);
    pauseMenu->hide();

    model = new GameModel();
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(16);

    connect(pauseMenuUi->resumeButton, &QPushButton::clicked, this, &Game::resumeGame);
    connect(pauseMenuUi->endGameButton, &QPushButton::clicked, this, &Game::on_endGameButton_clicked);
}

void Game::on_endGameButton_clicked()
{
    qDebug() << "Game ended!";
    emit endGame();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (pauseMenu->isHidden())
            pauseGame();
        else
            resumeGame();
    }
}

void Game::resumeGame()
{
    model->resume();
    pauseMenu->hide();
}

void Game::pauseGame()
{
    model->pause();
    pauseMenu->show();
}

void Game::updateView()
{
    model->update();
}

Game::~Game()
{
    delete ui;
    delete model;
}
