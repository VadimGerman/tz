#ifndef SALES_H
#define SALES_H

#include "Clerk.h"

class Sales : public Clerk
{
public:
    virtual QString getType() const;
    virtual float getIncrement() const;
    virtual float getMaxIncrement() const;
};

#endif // SALES_H
