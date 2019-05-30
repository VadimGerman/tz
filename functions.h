#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <memory>
#include "DataBase.h"

float computeSalary(Clerk *clerk, QDate date, std::shared_ptr<DataBase> &db);

#endif // FUNCTIONS_H
