#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "components/iconbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IconButton *SettingsIcon = new IconButton();
    ui->gridLayout->addWidget(SettingsIcon, 0, 1);

//SettingsIcon->changeBackgroundImage(":/assets/icons/gear.png");
    SettingsIcon->move(256, 256);
}

MainWindow::~MainWindow()
{
    delete ui;
}
