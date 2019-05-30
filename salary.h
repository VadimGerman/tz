#ifndef SALARY_H
#define SALARY_H

#include "Clerk.h"

class Salary
{
public:
    virtual ~Salary() {}

    virtual float compute(Clerk *clerk, QDate date) = 0;
};

#endif // SALARY_H
