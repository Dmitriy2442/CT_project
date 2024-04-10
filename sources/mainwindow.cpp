#include "../headers/mainwindow.h"
#include "../headers/charselect.h"

#include "../ui/ui_mainwindow.h"
#include "../ui/ui_mainmenu.h"
#include "../ui/ui_authors.h"
#include "../ui/ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , palette(":/palette/palette.txt")
{
    // Определение словарь соответствий названия интерфейса и его индекса в stackedWidget:
    ui2idx["mainMenu"] = 0;
    ui2idx["authors"] = 1;
    ui2idx["settings"] = 2;
    ui2idx["charSelect"] = 3;

    // Задание интерфейсных форм:
    Ui::MainMenuForm* mainMenuUi = new Ui::MainMenuForm();
    Ui::AuthorsForm* authorsUi = new Ui::AuthorsForm();
    Ui::SettingsForm* settingsUi = new Ui::SettingsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    settingsUi->setupUi(ui->settings);
    setCentralWidget(ui->stackedWidget);

    // Общая настройка дизайна
    this->setFixedSize(1280, 720);
    setStyleSheet("background-color: #222222");
    updateAllFonts();
    updateAllColors(ui->mainMenu);

    // Задание функций кнопкам:
    connect(mainMenuUi->gameButton, SIGNAL(clicked()), this, SLOT(goToCharSelectPage()));
    connect(mainMenuUi->exitIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(mainMenuUi->authorsIcon, SIGNAL(clicked()), this, SLOT(goToAuthorsPage()));
    connect(mainMenuUi->settingsIcon, SIGNAL(clicked()), this, SLOT(goToSettingsPage()));

    connect(authorsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));

    connect(settingsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));

    // connect(charSelectUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));
}

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value)
{
    QRegularExpression regExp(field + "\\s*:\\s*[^;]+;");
    QString replacement = field + ": " + value + ";";

    QString updatedStyleSheet = styleSheet;
    updatedStyleSheet.replace(regExp, replacement);

    return updatedStyleSheet;
}

void MainWindow::updateAllFonts()
{
    foreach (QWidget *widget, QApplication::allWidgets()) {
        widget->setFont(QApplication::font());
        widget->update();
    }
}

void MainWindow::updateAllColors(QWidget *page)
{
    palette.resetIterator();
    foreach (QObject *object, page->children()) {
        const char* objectType = object->metaObject()->className();
        QWidget* widget = qobject_cast<QWidget*>(object);
        if ((strcmp(objectType, "QLabel") == 0) || (strcmp(objectType, "QPushButton") == 0))
        {

            widget->setStyleSheet(updateStyleSheet(widget->styleSheet(), QString("color"), palette.getColor()));
            widget->update();

        } else if (strcmp(objectType, "IconButton") == 0) {

            IconButton* iconButton = qobject_cast<IconButton*>(widget);
            iconButton->updateColor(widget->styleSheet(), palette.getColor(), widget->size());
            widget->update();

        }
    }
}


void MainWindow::goToCharSelectPage()
{
    updateAllColors(ui->charSelect);
    ui->stackedWidget->setCurrentIndex(ui2idx["charSelect"]);
}

void MainWindow::goToMainMenuPage()
{
    updateAllColors(ui->mainMenu);
    ui->stackedWidget->setCurrentIndex(ui2idx["mainMenu"]);
}

void MainWindow::goToAuthorsPage()
{
    updateAllColors(ui->authors);
    ui->stackedWidget->setCurrentIndex(ui2idx["authors"]);
}

void MainWindow::goToSettingsPage()
{
    updateAllColors(ui->settings);
    ui->stackedWidget->setCurrentIndex(ui2idx["settings"]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
