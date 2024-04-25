#include "../headers/dbcontroller.h"

DBController::DBController() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gamedata.db");
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
    } else {
        qDebug() << "Database successfully opened";
    }
};

QVector<QPair<QString, QString>> DBController::getCharactersData(QVector<QString> names) {
    db.open();
    QSqlQuery query;

    if (names.isEmpty()) {
        query.prepare("SELECT name, imagePath FROM characters");
    } else {
        query.prepare("SELECT name, imagePath FROM characters WHERE name = :name");
        query.bindValue(":name", names);
    }

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QVector<QPair<QString, QString>>();
    }

    int resultCount = 0;
    QVector<QPair<QString, QString>> charactersData;
    while (query.next()) {
        charactersData.append(qMakePair(query.value(0).toString(), query.value(1).toString()));
        ++resultCount;
    }
    if (resultCount == 0) {
        qDebug() << "No results found for the given query (characters)";
    }

    db.close();
    return charactersData;
}

QVector<QString> DBController::getColorPalette(QString color)
{
    db.open();
    QSqlQuery query;

    if (!color.isEmpty()) {
        query.prepare("SELECT hex FROM palette WHERE color = :color");
        query.bindValue(":color", color);
    } else {
        query.prepare("SELECT hex FROM palette");
    }

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QVector<QString>();
    }

    int resultCount = 0;
    QVector<QString> palette;
    while (query.next()) {
        palette.append(query.value(0).toString());
        ++resultCount;
    }
    if (resultCount == 0) {
        qDebug() << "No results found for the given query (palette)";
    }

    db.close();
    return palette;
}
