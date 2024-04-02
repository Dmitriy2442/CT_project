#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "components/iconbutton.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Настройка главного layout'а
    ui->gridLayoutWidget->setFixedSize(1280, 720);
    ui->gridLayout->setContentsMargins(0, 50, 0, 50);

    // Создание layout'ов для названия игры и для кнопок
    auto *titleLayout = new QVBoxLayout(this);
    auto *buttonsLayout = new QGridLayout(this);
    buttonsLayout->setSpacing(40);
    buttonsLayout->setContentsMargins(40, 80, 40, 80);

    // Название игры
    auto *title = new QLabel("SAY GEX", this);
    title->setStyleSheet("font: italic Arial");
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 72);
    title->setFont(titleFont);

    titleLayout->addWidget(title);
    titleLayout->setSpacing(50);

    // Кнопка Game! и иконки
    auto *gameButton = new QPushButton("Game!", this);
    gameButton->setStyleSheet("QPushButton {"
                              "font: italic 'Arial';"
                              "font-size: 40px;"
                              "border: none;" // Убираем границу
                              "}");

    IconButton *ExitIcon = new IconButton();
    IconButton *SettingsIcon = new IconButton();
    IconButton *AutorsIcon = new IconButton();

    SettingsIcon->changeBackgroundImage(":/assets/icons/gear.png");
    ExitIcon->changeBackgroundImage(":/assets/icons/x.png");

    buttonsLayout->addWidget(gameButton, 0, 1, Qt::AlignCenter);
    buttonsLayout->addWidget(ExitIcon, 1, 0, Qt::AlignCenter);
    buttonsLayout->addWidget(SettingsIcon, 1, 1, Qt::AlignCenter);
    buttonsLayout->addWidget(AutorsIcon, 1, 2, Qt::AlignCenter);
    buttonsLayout->setSpacing(50);

    // Добавление всех обоих layout'ов в gridLayout
    ui->gridLayout->addLayout(titleLayout, 0, 0, Qt::AlignCenter);
    ui->gridLayout->addLayout(buttonsLayout, 1, 0, Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
