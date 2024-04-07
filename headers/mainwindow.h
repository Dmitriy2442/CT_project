#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public slots:
    void goToMainMenuPage();
    void goToAuthorsPage();
    void goToSettingsPage();

private:
    QHash<QString, int> ui2idx;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
