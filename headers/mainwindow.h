#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers/dbcontroller.h"
#include "headers/charSelect.h"
#include "headers/game.h"
#include "components/iconbutton.h"

#include <QMainWindow>
#include <QPalette>
#include <QLabel>
#include <QFontDatabase>
#include <QStackedWidget>
#include <QRegularExpression>

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
    void goToAuthorsPage();
    void goToSettingsPage();
    void beginGame();

private:
    QHash<QString, int> const ui2idx = {{"mainMenu", 0}, {"authors", 1}, {"settings", 2},
                                        {"charSelect", 3}, {"game", 4}};

    QVector<QString> palette;
    int paletteIterator = 0;

    Ui::MainWindow *ui;
    CharSelect *charSelect;
};

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value);

#endif // MAINWINDOW_H
