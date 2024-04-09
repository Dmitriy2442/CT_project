#include "headers/mainwindow.h"
#include "headers/colorpalette.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlTableModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Инициализация палитры цветов приложения
    ColorPalette* Palette = new ColorPalette(":/palette/palette.txt");

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
