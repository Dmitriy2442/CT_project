#include "mainwindow.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/nightmare.ttf");
    if (fontId != -1) {
        // Получение названия шрифта
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // Установка шрифта по умолчанию для приложения
        QApplication::setFont(QFont(fontFamily));
    } else {
        qDebug() << "Warning, failed to load font.";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
