#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Clerk.h"

class DataBase
{
    QSqlDatabase m_sdb;

    void sqlQueryToClerksList(QSqlQuery &query, QList<Clerk *> *clerks) const;

public:
    DataBase() = delete;
    DataBase(const QString &name);
    ~DataBase();

    Clerk *getClerk(int id);
    QList<Clerk *> *getClerkList(const QString &condition = "");
    bool addClerk(Clerk *clerk);
    bool delClerk(Clerk *clerk);
    bool delClerk(int id);

};

#endif // DATABASE_H
