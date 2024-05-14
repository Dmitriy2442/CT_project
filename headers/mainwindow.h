#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers/dbcontroller.h"
#include "headers/charSelect.h"
#include "headers/game.h"
#include "components/iconbutton.h"
#include "headers/history.h"

#include <QMainWindow>
#include <QPalette>
#include <QLabel>
#include <QFontDatabase>
#include <QStackedWidget>
#include <QRegularExpression>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateAllFonts();
    void updateAllColors(QWidget *page);

public slots:
    void goToCharSelectPage();
    void goToMainMenuPage();
    void goToHistoryPage();
    void goToSettingsPage();
    void beginGame();
    void gameEnded(QString name1, QString name2, QString winner);

signals:
    void updateHistory(QVector<QVector<QString>> matches);

private:
    QHash<QString, int> const ui2idx = {{"mainMenu", 0}, {"history", 1}, {"settings", 2},
                                        {"charSelect", 3}, {"game", 4}};

    QVector<QString> palette;
    int paletteIterator = 0;

    DBController *db;

    Ui::MainWindow *ui;
    HistoryForm *history;
    CharSelect *charSelect;
};

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value);

#endif // MAINWINDOW_H
