#include "SalesDecorator.h"
#include "functions.h"

float SalesDecorator::recursionCompute(Clerk *clerk, QDate &date)
{
    const float SUBORD_INCREASE = 0.003f; // 0.3%.
    float result = 0.0f;
    auto subord = m_db->getClerkList(QString("WHERE head_id='%1'")
                                  .arg(clerk->id));
    if (subord != nullptr)
        for (auto &subordinate : *subord)
        {
            result += computeSalary(subordinate, date, m_db) *
                    SUBORD_INCREASE;
            result += recursionCompute(subordinate, date);
        }
    else
        return 0.0f;

    while(!subord->empty())
    {
        delete subord->front();
        subord->pop_front();
    }
    delete subord;

    return result;
}

float SalesDecorator::compute(Clerk *clerk, QDate date)
{
    return m_component->compute(clerk, date) + recursionCompute(clerk, date);
}
