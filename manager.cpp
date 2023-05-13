#include "manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)


Manager *Manager::instance()
{
    return GlobalManager;
}


void Manager::clear() {
    measurement_count = 0;
}


