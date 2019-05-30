#include "Manager.h"


QString Manager::getType() const
{
    return QString("Manager");
}

float Manager::getIncrement() const
{
    return 0.05f;   // 5%.
}

float Manager::getMaxIncrement() const
{
    return 0.4f;    // 40%.
}
