#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QSqlError>

class DBController : public QObject  {
    Q_OBJECT
private:
    QSqlDatabase db;

public:
    DBController();

    QVector<QPair<QString, QString>> getCharactersData(QVector<QString> names = {});
    QVector<QString> getColorPalette(QString color = "");
    void insertMatchResults(const QString &name1, const QString &name2, const QString &winner);
    QVector<QVector<QString>> getLast5MatchResults();
};

#endif // DBCONTROLLER_H
