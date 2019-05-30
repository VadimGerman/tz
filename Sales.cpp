#include "Sales.h"


QString Sales::getType() const
{
    return QString("Sales");
}

float Sales::getIncrement() const
{
    return 0.01f;   // 1%.
}

float Sales::getMaxIncrement() const
{
    return 0.35f;   // 35%.
}
