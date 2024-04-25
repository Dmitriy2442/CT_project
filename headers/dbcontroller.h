#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QSqlError>

class DBController {
private:
    QSqlDatabase db;

public:
    DBController();
    QVector<QPair<QString, QString>> getCharactersData(QVector<QString> names = {});
    /* TODO: Функция, которая получает из одного или сразу из двух имен всю необходимую для создания игровых персонажей информацию
        (я не знаю какая информация нужна для этого, это целиком на игровой логике висит) */


    QVector<QString> getColorPalette(QString color = "");
};

#endif // DBCONTROLLER_H
