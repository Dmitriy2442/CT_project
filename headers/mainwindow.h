#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void getChosenCharsNames(const QString &name1, const QString &name2);

private:
    QHash<QString, int> ui2idx;

    QVector<QString> palette;
    int paletteIterator = 0;

    QVector<QString> chosenNames = {"", ""};

    Ui::MainWindow *ui;
};

QString updateStyleSheet(const QString &styleSheet, const QString &field, const QString &value);

#endif // MAINWINDOW_H
