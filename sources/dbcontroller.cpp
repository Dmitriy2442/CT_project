#include "../headers/dbcontroller.h"

DBController::DBController() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gamedata.db");
    qDebug() << "Database opened";
};

void DBController::getCharactersData(QVector<int> &ids, QVector<QString> &names, QVector<QString> &imagePaths) {
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
