#ifndef CHARACTER_DATABASE_H
#define CHARACTER_DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

void initializeDatabase();
void addCharacter(const QString &name, const QString &imagePath);



#endif // CHARACTER_DATABASE_H
