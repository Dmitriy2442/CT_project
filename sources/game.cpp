#include "headers/game.h"

#include "../ui/ui_game.h"
#include "../ui/ui_pausemenu.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    pauseMenu = new QWidget(this);
    Ui::PauseMenuForm* pauseMenuUi = new Ui::PauseMenuForm();
    pauseMenuUi->setupUi(pauseMenu);
    pauseMenu->hide();

    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGeometry(0, 0, 1280, 720);

    arena = new Arena(this);
    view->setScene(arena);
    arena->setupArena(QSize(1280, 720));

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Game::updateView);
    updateTimer->start(16);

    connect(pauseMenuUi->resumeButton, &QPushButton::clicked, this, &Game::resumeGame);
    connect(pauseMenuUi->endGameButton, &QPushButton::clicked, this, &Game::endGameButtonClicked);
}

void Game::endGameButtonClicked()
{
    qDebug() << "Game ended!";
    emit endGameSignal();
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

void Game::updateView()
{
    // Update view here
}

void Game::startGame()
{
    // Start game here
}

void Game::pauseGame()
{
    pauseMenu->show();
    pauseMenu->raise();
}

void Game::resumeGame()
{
    pauseMenu->hide();
}

void Game::endGame()
{
    // End game here
}

Game::~Game()
{
    delete ui;
}
