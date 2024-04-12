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
    // Общая идея в том, чтобы не перегружать функции и делать их более специфицированными, учитывая, что они будут вызываться буквально два раза
    void getCharactersData(QVector<int> &ids, QVector<QString> &names, QVector<QString> &imagePaths); // Комменты в cpp
    /* TODO: Функция, которая получает из одного или сразу из двух имен всю необходимую для создания игровых персонажей информацию
        (я не знаю какая информация нужна для этого, это целиком на игровой логике висит) */
};

#endif // DBCONTROLLER_H
