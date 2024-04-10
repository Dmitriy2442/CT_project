#include "headers/character_database.h"

void initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Устанавливаем название файла базы данных
    db.setDatabaseName("gamedata.db");

    // Пытаемся открыть базу данных
    if (!db.open()) {
        qDebug() << "Ошибка при открытии базы данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS characters ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "name TEXT NOT NULL, "
                              "imagePath TEXT NOT NULL)");

    if (!success) {
        qDebug() << "Ошибка при создании таблицы: " << query.lastError().text();
    }

    addCharacter("Dimas", "assets/characters/Dimas.png");
}

void addCharacter(const QString &name, const QString &imagePath) {
    QSqlQuery query;
    query.prepare("INSERT INTO characters (name, imagePath) VALUES (:name, :imagePath)");
    query.bindValue(":name", name);
    query.bindValue(":imagePath", imagePath);

    if (!query.exec()) {
        qDebug() << "Ошибка при добавлении персонажа: " << query.lastError().text();
    }
}
