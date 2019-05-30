#ifndef MANAGER_H
#define MANAGER_H

#include "Clerk.h"

class Manager : public Clerk
{
public:
    virtual QString getType() const;
    virtual float getIncrement() const;
    virtual float getMaxIncrement() const;
};

#endif // MANAGER_H
