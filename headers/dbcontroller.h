#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class DBController {
private:
    QSqlDatabase db;

public:
    DBController();
    void getCharactersData(QVector<int> &ids, QVector<QString> &names, QVector<QString> &imagePaths);

};

#endif // DBCONTROLLER_H
