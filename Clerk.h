#ifndef CLERK_H
#define CLERK_H

#include <QString>
#include <QDate>

class Clerk
{
public:
    int id;
    int head;
    QString name;
    QDate date;
    float salary;

    virtual ~Clerk() {}

    virtual QString getType() const = 0;
    virtual float getIncrement() const = 0;
    virtual float getMaxIncrement() const = 0;
};

#endif // CLERK_H
