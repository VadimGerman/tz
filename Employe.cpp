#include "Employe.h"

QString Employee::getType() const
{
    return QString("Employee");
}

float Employee::getIncrement() const
{
    return 0.03f;   // 3%.
}

float Employee::getMaxIncrement() const
{
    return 0.3f;    // 30%.
}
