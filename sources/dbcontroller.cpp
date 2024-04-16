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

void DBController::getCharactersData(QVector<int> &ids, QVector<QString> &names, QVector<QString> &imagePaths) {
    /* Функция, возвращающая заполненные массивы с именами и путями к картинке для всех элементов таблицы characters:
     * names, imagePaths - ссылки на пустые массивы
     * можно ей будет начхать на айдишники, пожалуйста, мне просто нужны все элементы этой таблицы для экрана выбора персонажей
    */
    db.open();
    QSqlQuery query;

    query.prepare("SELECT name, imagePath FROM your_table WHERE id = :id");
    for (int i = 0; i < ids.size(); i++) {
        query.bindValue(":id", ids[i]);

        if (!query.exec()) {
            qDebug() << "Error executing query";
        }
        else {
            names[i] = query.value(0).toString();
            imagePaths[i] = query.value(1).toString();
            qDebug() << "Name:" << names[i] << ", Image Path:" << imagePaths[i];
        }
    }
    db.close();
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
