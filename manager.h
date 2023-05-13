#ifndef MANAGER_H
#define MANAGER_H

#include "plots/plot.h"
#include <QGlobalStatic>

class Manager
{
public:

   void clear();
   static Manager* instance();

   Plot *plot;
private:
   int measurement_count = 0;
};

#endif // MANAGER_H
