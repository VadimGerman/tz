#ifndef MANAGERDECORATOR_H
#define MANAGERDECORATOR_H

#include <memory>
#include "Salary.h"
#include "DataBase.h"

class ManagerDecorator : public Salary
{
    std::shared_ptr<Salary> m_component;
    std::shared_ptr<DataBase> m_db;

public:
    ManagerDecorator(Salary *component, std::shared_ptr<DataBase> &db) :
        m_component(component),
        m_db(db)
    {}

    virtual float compute(Clerk *clerk, QDate date);
};

#endif // MANAGERDECORATOR_H
