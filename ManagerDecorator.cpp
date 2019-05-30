#include "ManagerDecorator.h"
#include "functions.h"

float ManagerDecorator::compute(Clerk *clerk, QDate date)
{
    const float SUBORD_INCREASE = 0.005f;  // 0.5%.
    float salaryIncrease = 0.0f;
    auto subord = m_db->getClerkList(QString("WHERE head_id='%1'")
                                   .arg(clerk->id));
    for (auto &subordinate : *subord)
        salaryIncrease += computeSalary(subordinate, date, m_db) * SUBORD_INCREASE;

    while(!subord->empty())
    {
        delete subord->front();
        subord->pop_front();
    }
    delete subord;

    return m_component->compute(clerk, date) + salaryIncrease;
}
