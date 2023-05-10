#ifndef IMPCSV_H
#define IMPCSV_H

#include<QWidget>
#include "imp.h"

class IMPCSV : public IO
{Q_OBJECT
public:
    IMPCSV(QWidget* parent = nullptr);
    ~IMPCSV();

    virtual QString save() override;
    virtual void load(QString input) override;
private:
};

#endif // IMPCSV_H
