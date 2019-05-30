#ifndef SALESDECORATOR_H
#define SALESDECORATOR_H

#include <memory>
#include "Salary.h"
#include "DataBase.h"

class SalesDecorator : public Salary
{
    std::shared_ptr<Salary> m_component;
    std::shared_ptr<DataBase> m_db;

    float recursionCompute(Clerk *clerk, QDate &date);

public:
    SalesDecorator(Salary *component, std::shared_ptr<DataBase> &db) :
        m_component(component),
        m_db(db)
    {}

    virtual float compute(Clerk *clerk, QDate date);
};

#endif // SALESDECORATOR_H
