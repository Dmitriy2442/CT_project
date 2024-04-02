#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "components/iconbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IconButton *newButton = new IconButton();
    ui->gridLayout->addWidget(newButton, 0, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
