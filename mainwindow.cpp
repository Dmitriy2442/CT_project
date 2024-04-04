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
    // Определим словарь соответствий названия интерфейса и его индекса в stackedWidget:
    ui2idx["mainMenu"] = 0;
    ui2idx["authors"] = 1;

    //
    auto mainMenuUi = new Ui::MainMenuForm();
    auto authorsUi = new Ui::AuthorsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    setCentralWidget(ui->stackedWidget);

    // Задание функций кнопкам:
    connect(mainMenuUi->exitIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(mainMenuUi->authorsIcon, SIGNAL(clicked()), this, SLOT(goToAuthorsPage()));



    // Подгрузка шрифта для названия:
    //int bangerstId = QFontDatabase::addApplicationFont(":/fonts/bangers.ttf");
    //QString bangersFamily = QFontDatabase::applicationFontFamilies(bangerstId).at(0);;
    //ui->title->setFont(QFont(bangersFamily, 128));

}

void MainWindow::goToAuthorsPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["authors"]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
