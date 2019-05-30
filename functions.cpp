
#include "functions.h"
#include "SalaryExperience.h"
#include "ManagerDecorator.h"
#include "SalesDecorator.h"

float computeSalary(Clerk *clerk, QDate date, std::shared_ptr<DataBase> &db)
{
    QString type = clerk->getType();
    Salary *salary = nullptr;
    if (type == "Employee")
        salary = new SalaryExperience();
    else if (type == "Manager")
        salary = new ManagerDecorator(new SalaryExperience(), db);
    else if (type == "Sales")
        salary = new SalesDecorator(new SalaryExperience(), db);

    if (salary == nullptr)
        return 0.0f;

    return salary->compute(clerk, date);
}
