#include "headers/mainwindow.h"
#include "headers/character_database.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Инициализация базы данных
    initializeDatabase();

    // Установка шрифта по умолчанию
    int fontId = QFontDatabase::addApplicationFont(":/fonts/nightmare.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QApplication::setFont(QFont(fontFamily));
    } else {
        qDebug() << "Warning, failed to load font.";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
