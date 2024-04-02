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

    //newButton->resize(128, 128);
    SettingsIcon->setText("");
    SettingsIcon->move(256, 256);
}

MainWindow::~MainWindow()
{
    delete ui;
}
