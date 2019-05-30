#include <QDebug>
#include "DataBase.h"
#include "Employe.h"
#include "Manager.h"
#include "Sales.h"

const QString DB_TYPE = "QSQLITE";

DataBase::DataBase(const QString &name)
{
    m_sdb = QSqlDatabase::addDatabase(DB_TYPE);
    m_sdb.setDatabaseName(name);
    if (!m_sdb.open())
    {
        qDebug() << m_sdb.lastError().text();
    }
}

DataBase::~DataBase()
{
    m_sdb.close();
}

Clerk *DataBase::getClerk(int id)
{
    auto list = getClerkList(QString("WHERE id='%1'").arg(id));

    Clerk *out = nullptr;
    if (list != nullptr)
    {
        out = list->first();
        delete list;
    }

    return out;
}

QList<Clerk *> *DataBase::getClerkList(const QString &condition)
{
    QList<Clerk *> *result = new QList<Clerk *>;
    QString request = "SELECT id, name, type, date, salary FROM Employees";
    if (!condition.isEmpty())
        request += " " + condition;

    QSqlQuery query;
    query.exec(request);
    sqlQueryToClerksList(query, result);
    if (result->empty())
    {
        delete result;
        result = nullptr;
    }

    return result;
}

bool DataBase::addClerk(Clerk *clerk)
{
    QString request = QString("INSERT INTO \"Employees\" (\"type\", \"name\", \"date\", \"salary\", \"head_id\")"
                       "VALUES (\"%1\", \"%2\", \"%3\", %4, %5)")
            .arg(clerk->getType())
            .arg(clerk->name)
            .arg(clerk->date.toString("yyyyMMdd"))
            .arg(clerk->salary)
            .arg(clerk->head);
    QSqlQuery query;

    return query.exec(request);
}

bool DataBase::delClerk(Clerk *clerk)
{
    int id = clerk->id;
    delete clerk;

    return delClerk(id);
}

bool DataBase::delClerk(int id)
{
    QString request = QString("DELETE FROM Employees WHERE id='%1'")
            .arg(id);
    QSqlQuery query;

    return query.exec(request);
}

void DataBase::sqlQueryToClerksList(QSqlQuery &query, QList<Clerk *> *clerks) const
{
    while (query.next())
    {
        // Тут можно было бы использовать фабрику.
        QString type = query.value(2).toString();
        Clerk *clerk = nullptr;
        if (type == "Employee")
            clerk = new Employee();
        else if (type == "Manager")
            clerk = new Manager();
        else if (type == "Sales")
            clerk = new Sales();

        if (clerk == nullptr)
            continue;

        clerk->id = query.value(0).toInt();
        clerk->name = query.value(1).toString();
        clerk->date = QDate::fromString(query.value(3).toString(), "yyyyMMdd");
        clerk->salary = query.value(4).toFloat();

        clerks->push_back(clerk);
    }
}
