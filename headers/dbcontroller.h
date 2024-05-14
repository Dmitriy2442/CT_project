#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QSqlError>

class DataManager : public QObject {
    Q_OBJECT

signals:
    void requestCharactersData(QVector<QString> names);
    void requestColorPalette(QString color);
    void requestInsertMatchResults(QString name1, QString name2, QString winner);
};

class DBController : public QObject  {
    Q_OBJECT
private:
    QSqlDatabase db;

public:
    DBController();

    QVector<QPair<QString, QString>> getCharactersData(QVector<QString> names = {});
    QVector<QString> getColorPalette(QString color = "");
    void insertMatchResults(const QString &name1, const QString &name2, const QString &winner);

public slots:
    void handleCharactersDataRequest(QVector<QString> names);
    void handleColorPaletteRequest(QString color);
    void handleInsertMatchResultsRequest(QString name1, QString name2, QString winner);

signals:
    void charactersDataReceived(const QVector<QPair<QString, QString>>& data);
    void colorPaletteReceived(const QVector<QString>& data);
    void matchResultsInserted();
};

#endif // DBCONTROLLER_H
