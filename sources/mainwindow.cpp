#include "headers/mainwindow.h"

#include "../ui/ui_mainwindow.h"
#include "../ui/ui_mainmenu.h"
#include "../ui/ui_authors.h"
#include "../ui/ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Инициализация базы данных приложения
    DBController db;
    palette = db.getColorPalette("pink");
    qDebug() << db.getCharactersData();
    charSelect = new CharSelect(db.getCharactersData());

    // Задание интерфейсных форм:
    Ui::MainMenuForm* mainMenuUi = new Ui::MainMenuForm();
    Ui::AuthorsForm* authorsUi = new Ui::AuthorsForm();
    Ui::SettingsForm* settingsUi = new Ui::SettingsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    authorsUi->setupUi(ui->authors);
    settingsUi->setupUi(ui->settings);
    ui->stackedWidget->removeWidget(ui->charSelect);
    ui->stackedWidget->insertWidget(ui2idx["charSelect"], charSelect);
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

    connect(charSelect, SIGNAL(on_backIcon_clicked()), this, SLOT(goToMainMenuPage()));
    connect(charSelect, &CharSelect::playersChose, this, &MainWindow::getChosenCharsNames);
    connect(charSelect, &CharSelect::beginGame, this, &MainWindow::beginGame);

    connect(ui->game, &Game::endGame, this, &MainWindow::goToMainMenuPage);
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
    paletteIterator = 0;
    foreach (QObject *object, page->children()) {
        const char* objectType = object->metaObject()->className();
        QWidget* widget = qobject_cast<QWidget*>(object);
        if ((strcmp(objectType, "QLabel") == 0) || (strcmp(objectType, "QPushButton") == 0))
        {

            widget->setStyleSheet(updateStyleSheet(widget->styleSheet(), QString("color"), palette[paletteIterator]));
            widget->update();

        } else if (strcmp(objectType, "IconButton") == 0) {

            IconButton* iconButton = qobject_cast<IconButton*>(widget);
            iconButton->updateColor(widget->styleSheet(), palette[paletteIterator], widget->size());

            widget->update();
        }
        paletteIterator = (paletteIterator + 1) % palette.length();
    }
}


void MainWindow::goToCharSelectPage()
{
    charSelect->setUpClear();
    updateAllColors(charSelect);
    updateAllColors(charSelect->readyOverlay);
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

void MainWindow::beginGame()
{
    updateAllColors(ui->game);
    ui->stackedWidget->setCurrentIndex(ui2idx["game"]);
}

void MainWindow::getChosenCharsNames(const QString &name1, const QString &name2) {
    chosenNames[0] = name1;
    chosenNames[1] = name2;
    qDebug() << "Main window got these character names: " << name1 << "and" << name2;
}

MainWindow::~MainWindow()
{
    delete ui;
}
