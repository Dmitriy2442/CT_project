#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui/ui_mainmenu.h"
#include "./ui/ui_authors.h"

#include <QLabel>
#include <QFontDatabase>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    auto mainMenuUi = new Ui::MainMenuForm();
    auto authorsUi = new Ui::AuthorsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    setCentralWidget(ui->stackedWidget);



    // Подгрузка шрифта для названия
    //int bangerstId = QFontDatabase::addApplicationFont(":/fonts/bangers.ttf");
    //QString bangersFamily = QFontDatabase::applicationFontFamilies(bangerstId).at(0);;
    //ui->title->setFont(QFont(bangersFamily, 128));

}

MainWindow::~MainWindow()
{
    delete ui;
}
