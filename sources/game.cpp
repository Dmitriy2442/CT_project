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

    endGameMenu = ui->endGameMenu;
    endGameMenu->hide();

    ui->pressToStart->show();
    ui->pressToStart->raise();

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
    player1Controller = new PlayerController(0, player1);
    view->installEventFilter(player1Controller); // Подключение контроллера к виджету
    connect(this, &Game::updateTick, player1Controller, &PlayerController::update);

    // Создание 2-го игрока
    player2 = new Character(1, ":/samurai_red", arena->getPlatforms(), attackZones);
    arena->addItem(player2);
    player2->setPos(arena->initPos2().first, arena->initPos2().second);
    connect(player2, &Character::death, this, &Game::playerDead);

    // Создание контроллера для 2-го игрока
    player2Controller = new PlayerController(1, player2);
    view->installEventFilter(player2Controller); // Подключение контроллера к виджету
    connect(this, &Game::updateTick, player2Controller, &PlayerController::update);
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
    ui->winnerLabel->setText(names[(id+1)%2] + " wins!");
    gameTimer->stop();
    endGameMenu->show();
    endGameMenu->raise();
}

void Game::endGameButtonClicked()
{
    qDebug() << "End game button clicked!";
    endGame();
}

void Game::getNames(const QString &name1, const QString &name2)
{
    names[0] = name1;
    names[1] = name2;
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

void Game::startGame() {
    // Start game timer
    gameTimer->start();
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
    setupClear();
}

void Game::setupClear() {
    // Reset all character locations, speed and health
    player1->setPos(arena->initPos1().first, arena->initPos1().second);
    player1->setVelocity(0, 0);
    player1->setHealth(300);
    player2->setPos(arena->initPos2().first, arena->initPos2().second);
    player2->setVelocity(0, 0);
    player2->setHealth(300);

    // Hide all interfaces
    endGameMenu->hide();
    pauseMenu->hide();

    // Show PressToStart interface
    ui->pressToStart->show();
    ui->pressToStart->raise();
}

Game::~Game()
{
    delete ui;
}
