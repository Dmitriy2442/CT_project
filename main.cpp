#include "headers/mainwindow.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


void initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Устанавливаем название файла базы данных
    db.setDatabaseName("gamedata.db");

    // Пытаемся открыть базу данных
    if (!db.open()) {
        qDebug() << "Ошибка при открытии базы данных:" << db.lastError().text();
        return;
    }
}

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
