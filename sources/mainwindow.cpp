#include "../headers/mainwindow.h"

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

    // Задание интерфейсных форм:
    Ui::MainMenuForm* mainMenuUi = new Ui::MainMenuForm();
    Ui::AuthorsForm* authorsUi = new Ui::AuthorsForm();
    Ui::SettingsForm* settingsUi = new Ui::SettingsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    settingsUi->setupUi(ui->settings);
    setCentralWidget(ui->stackedWidget);

    this->setStyleSheet("background-color: #222222");
    this->updateAllFonts();
    this->updateAllColors();

    // Задание функций кнопкам:
    connect(mainMenuUi->exitIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(mainMenuUi->authorsIcon, SIGNAL(clicked()), this, SLOT(goToAuthorsPage()));
    connect(mainMenuUi->settingsIcon, SIGNAL(clicked()), this, SLOT(goToSettingsPage()));

    connect(authorsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));

    connect(settingsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));
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

void MainWindow::updateAllColors()
{
    palette.resetIterator();
    foreach (QWidget *widget, QApplication::allWidgets()) {
        const char* widgetType = widget->metaObject()->className();
        if ((strcmp(widgetType, "QLabel") == 0) || (strcmp(widgetType, "QPushButton") == 0))
        {

            widget->setStyleSheet(updateStyleSheet(widget->styleSheet(), QString("color"), palette.getColor()));

        } else if (strcmp(widgetType, "IconButton") == 0) {
            IconButton* iconButton = qobject_cast<IconButton*>(widget);
            iconButton->updateColor(widget->styleSheet(), palette.getColor(), widget->size());
        }
        widget->update();
    }
}

void MainWindow::goToAuthorsPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["authors"]);
    this->updateAllColors();
}

void MainWindow::goToMainMenuPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["mainMenu"]);
    this->updateAllColors();
}

void MainWindow::goToSettingsPage()
{
    ui->stackedWidget->setCurrentIndex(ui2idx["settings"]);
    this->updateAllColors();
}

MainWindow::~MainWindow()
{
    delete ui;
}
