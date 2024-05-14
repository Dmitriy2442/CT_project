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

    ui->endGameMenu->hide();

    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGeometry(0, 0, 1280, 720);

    // Настройка арены (класс Arena наследуется от QGraphicsScene)
    arena = new Arena(this);
    view->setScene(arena);
    arena->setupArena(QSize(1280, 720));

    //Настройка зон атаки
    QVector<attackZone> *attackZones = new QVector<attackZone>(2);
    (*attackZones)[0] = {QRectF(), 0};
    (*attackZones)[1] = {QRectF(), 0};

    // Создание 1-го игрока
    player1 = new Character(0, ":/samurai_blue", arena->getPlatforms(), attackZones);
    arena->addItem(player1);
    player1->setPos(arena->initPos1().first, arena->initPos1().second);
    connect(player1, &Character::death, this, &Game::playerDead);
    // Создание контроллера для 1-го игрока
    player1Controller = new PlayerController(player1);
    view->installEventFilter(player1Controller); // Подключение контроллера к виджету
    connect(this, &Game::updateTick, player1Controller, &PlayerController::update);

    // Создание 2-го игрока
    player2 = new Character(1, ":/samurai_red", arena->getPlatforms(), attackZones);
    arena->addItem(player2);
    player2->setPos(arena->initPos2().first, arena->initPos2().second);
    connect(player2, &Character::death, this, &Game::playerDead);



    // Таймер обновления игры
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameTimer->start(16);

    // Подключение кнопок
    connect(pauseMenuUi->resumeButton, &QPushButton::clicked, this, &Game::resumeGame);
    connect(pauseMenuUi->endGameButton, &QPushButton::clicked, this, &Game::endGameButtonClicked);
    connect(ui->homeIcon, &QPushButton::clicked, this, &Game::endGame);
}

void Game::updateGame()
{
    emit(updateTick());
}

void Game::playerDead(int id)
{
    qDebug() << "Player " << id << " died!";
    gameTimer->stop();
    ui->endGameMenu->show();
    ui->endGameMenu->raise();
}

void Game::endGameButtonClicked()
{
    qDebug() << "End game button clicked!";
    endGame();
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

void Game::startGame()
{
    // Start game here
}

void Game::pauseGame()
{
    pauseMenu->show();
    pauseMenu->raise();
    gameTimer->stop();
}

void Game::resumeGame()
{
    pauseMenu->hide();
    gameTimer->start();
}

void Game::endGame()
{
    qDebug() << "Game ended!";
    emit endGameSignal();
}

Game::~Game()
{
    delete ui;
}
