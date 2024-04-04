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
    // Определение словарь соответствий названия интерфейса и его индекса в stackedWidget:
    ui2idx["mainMenu"] = 0;
    ui2idx["authors"] = 1;

    // Задание интерфейсных форм:
    Ui::MainMenuForm* mainMenuUi = new Ui::MainMenuForm();
    Ui::AuthorsForm* authorsUi = new Ui::AuthorsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    setCentralWidget(ui->stackedWidget);

    this->setStyleSheet("background-color: #222222");
    this->updateAllFonts();

    // Задание функций кнопкам:
    connect(mainMenuUi->exitIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(mainMenuUi->authorsIcon, SIGNAL(clicked()), this, SLOT(goToAuthorsPage()));

    connect(authorsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));
}

void MainWindow::updateAllFonts()
{
    foreach (QWidget *widget, QApplication::allWidgets()) {
        widget->setFont(QApplication::font());
        widget->update();
    }
}

void MainWindow::goToAuthorsPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["authors"]);
}

void MainWindow::goToMainMenuPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["mainMenu"]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
