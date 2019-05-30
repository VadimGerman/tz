#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "Clerk.h"

class Employee : public Clerk
{
public:
    virtual QString getType() const;
    virtual float getIncrement() const;
    virtual float getMaxIncrement() const;
};

#endif // EMPLOYE_H
