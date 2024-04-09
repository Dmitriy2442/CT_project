#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers/colorpalette.h"
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
    void updateAllColors();

public slots:
    void goToMainMenuPage();
    void goToAuthorsPage();
    void goToSettingsPage();


private:
    QHash<QString, int> ui2idx;
    ColorPalette palette;

    Ui::MainWindow *ui;
};

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value);

#endif // MAINWINDOW_H
