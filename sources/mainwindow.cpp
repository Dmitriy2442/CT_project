#include "headers/mainwindow.h"

#include "../ui/ui_mainwindow.h"
#include "../ui/ui_mainmenu.h"
#include "../ui/ui_settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Инициализация базы данных приложения
    db = new DBController();
    QThread* dbThread = new QThread();
    db->moveToThread(dbThread);
    dbThread->start();

    palette = db->getColorPalette("pink");
    charSelect = new CharSelect(db->getCharactersData());
    history = new HistoryForm(db->getLast5MatchResults());

    // Задание интерфейсных форм:
    Ui::MainMenuForm* mainMenuUi = new Ui::MainMenuForm();
    Ui::SettingsForm* settingsUi = new Ui::SettingsForm();

    ui->setupUi(this);
    mainMenuUi->setupUi(ui->mainMenu);
    settingsUi->setupUi(ui->settings);
    ui->stackedWidget->removeWidget(ui->charSelect);
    ui->stackedWidget->insertWidget(ui2idx["charSelect"], charSelect);
    ui->stackedWidget->removeWidget(ui->history);
    ui->stackedWidget->insertWidget(ui2idx["history"], history);
    setCentralWidget(ui->stackedWidget);

    // Общая настройка дизайна
    this->setFixedSize(1280, 720);
    setStyleSheet("background-color: #222222");
    updateAllFonts();
    mainMenuUi->title->setFont({"Bauhaus 93", 18});
    updateAllColors(ui->mainMenu);

    QMovie *movie = new QMovie(":/images/menuback.gif");
    mainMenuUi->backgroundLabel->setMovie(movie);
    movie->start();


    // Задание функций кнопкам:
    connect(mainMenuUi->gameButton, SIGNAL(clicked()), this, SLOT(goToCharSelectPage()));
    connect(mainMenuUi->exitIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(mainMenuUi->historyIcon, SIGNAL(clicked()), this, SLOT(goToHistoryPage()));
    connect(mainMenuUi->settingsIcon, SIGNAL(clicked()), this, SLOT(goToSettingsPage()));

    connect(history, SIGNAL(on_backIcon_clicked()), this, SLOT(goToMainMenuPage()));
    connect(this, &MainWindow::updateHistory, history, &HistoryForm::updateHistory);

    connect(settingsUi->backIcon, SIGNAL(clicked()), this, SLOT(goToMainMenuPage()));
    connect(settingsUi->volumeSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(updateVolume(int)));

    connect(charSelect, SIGNAL(on_backIcon_clicked()), this, SLOT(goToMainMenuPage()));
    connect(charSelect, &CharSelect::playersChose, ui->game, &Game::getNames);
    connect(charSelect, &CharSelect::beginGame, this, &MainWindow::beginGame);
    connect(charSelect, &CharSelect::beginGame, ui->game, &Game::startGame);

    connect(ui->game, &Game::endGameSignal, this, &MainWindow::gameEnded);
}

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value)
{
    QRegularExpression bgColorRegExp("\\bbackground-color\\s*:\\s*([^;]+);");
    QRegularExpressionMatch bgColorMatch = bgColorRegExp.match(styleSheet);
    QString bgColorValue;
    if (bgColorMatch.hasMatch()) {
        bgColorValue = bgColorMatch.captured(1); // Сохраняем найденное значение background-color
    }

    // Изменяем значение color
    QRegularExpression colorRegExp("\\b" + QRegularExpression::escape(field) + "\\s*:\\s*([^;]+);");
    QString colorReplacement = field + ": " + value + ";";
    QString updatedStyleSheet = styleSheet;
    updatedStyleSheet.replace(colorRegExp, colorReplacement);

    // Возвращаем background-color обратно, если он был изменён
    if (!bgColorValue.isEmpty()) {
        QRegularExpression replaceBgColorRegExp("\\bbackground-color\\s*:\\s*([^;]+);");
        QString bgColorReplacement = "background-color: " + bgColorValue + ";";
        updatedStyleSheet.replace(replaceBgColorRegExp, bgColorReplacement);
    }

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

void MainWindow::goToHistoryPage()
{
    updateAllColors(history);
    ui->stackedWidget->setCurrentIndex(ui2idx["history"]);
}

void MainWindow::goToSettingsPage()
{
    updateAllColors(ui->settings);
    ui->stackedWidget->setCurrentIndex(ui2idx["settings"]);
}

void MainWindow::beginGame()
{
    ui->game->setupClear();
    updateAllColors(ui->game);
    updateAllColors(ui->game->pauseMenu);
    updateAllColors(ui->game->endGameMenu);
    ui->stackedWidget->setCurrentIndex(ui2idx["game"]);
}

void MainWindow::gameEnded(QString name1, QString name2, QString winner)
{
    if (!winner.isEmpty()) {
        // qDebug() << name1 << " vs " << name2 << " winner: " << winner;
        db->insertMatchResults(name1, name2, winner);
    }
    emit(updateHistory(db->getLast5MatchResults()));
    goToMainMenuPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}
