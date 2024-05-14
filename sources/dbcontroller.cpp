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

void DBController::insertMatchResults(const QString &name1, const QString &name2, const QString &winner)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO results (name1, name2, winner) VALUES (:name1, :name2, :winner)");
    query.bindValue(":name1", name1);
    query.bindValue(":name2", name2);
    query.bindValue(":winner", winner);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
    }

    db.close();
    qDebug() << "Inserted match results: " << name1 << " vs " << name2 << " winner: " << winner;
}

QVector<QVector<QString>> DBController::getLast5MatchResults() {
    db.open();
    QSqlQuery query;
    query.prepare("SELECT name1, name2, winner FROM results LIMIT 5");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QVector<QVector<QString>>();
    }

    int i = 0;
    QVector<QVector<QString>> last5MatchResults(5, QVector<QString>(3));

    while (query.next()) {
        QVector<QString> matchResults(3);
        matchResults[0] = query.value(0).toString();
        matchResults[1] = query.value(1).toString();
        matchResults[2] = query.value(2).toString();
        last5MatchResults[i] = matchResults;
        ++i;
    }

    if (i == 0) {
        qDebug() << "No results found for the given query (results)";
    }

    db.close();
    return last5MatchResults;
}
