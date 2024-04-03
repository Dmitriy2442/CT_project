#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подгрузка шрифта для названия
    int bangerstId = QFontDatabase::addApplicationFont(":/fonts/bangers.ttf");
    QString bangersFamily = QFontDatabase::applicationFontFamilies(bangerstId).at(0);;
    ui->title->setFont(QFont(bangersFamily, 128));
}

MainWindow::~MainWindow()
{
    delete ui;
}
