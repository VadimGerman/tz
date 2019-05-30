#include "SalaryExperience.h"

float SalaryExperience::compute(Clerk *clerk, QDate date)
{
    int dateDifference = date.year() - clerk->date.year();
    if (dateDifference < 0)
        return 0.0f;

    float increasePercent = dateDifference * clerk->getIncrement();
    if (increasePercent > clerk->getMaxIncrement())
        increasePercent = clerk->getMaxIncrement();

    float result = clerk->salary + clerk->salary * increasePercent;
    return result;
}
