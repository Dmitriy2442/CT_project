#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "components/iconbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IconButton *SettingsIcon = new IconButton();
    IconButton *ExitIcon = new IconButton();

    ui->gridLayout->addWidget(SettingsIcon, 0, 1);
    ui->gridLayout->addWidget(ExitIcon, 0, 2);

    SettingsIcon->changeBackgroundImage(":/assets/icons/gear.png");
    ExitIcon->changeBackgroundImage(":/assets/icons/x.png");
    SettingsIcon->move(256, 256);
}

MainWindow::~MainWindow()
{
    delete ui;
}
