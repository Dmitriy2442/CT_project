#include "mainwindow.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загрузка шрифтов из ресурсов
    int fontId = QFontDatabase::addApplicationFont(":/fonts/bangers.ttf");
    QString bangersFont = QFontDatabase::applicationFontFamilies(fontId).at(0);

    MainWindow w;
    w.show();
    return a.exec();
}
