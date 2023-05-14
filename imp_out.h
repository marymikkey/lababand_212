#ifndef STRATEGY_IO_H
#define STRATEGY_IO_H

#include "manager.h"



struct ImpOut
{
    virtual void save(const QString&) = 0;
    virtual void load(const QString&) = 0;
};

struct ImpOut_CSV : ImpOut
{
    virtual void save(const QString&) override;
    virtual void load(const QString&) override;
};


#endif // STRATEGY_IO_H
