#ifndef SALARYEXPERIENCE_H
#define SALARYEXPERIENCE_H

#include "Salary.h"

/*
 * Класс для подсчета ЗП с учетом стажа. Для сотрудников всех типов.
 **/
class SalaryExperience : public Salary
{
public:
    virtual float compute(Clerk *clerk, QDate date);
};

#endif // SALARYEXPERIENCE_H
