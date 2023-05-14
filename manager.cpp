#include "Manager.h"
#include <QGlobalStatic>
#include "Manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::addVariable(const VariableData & variable){
    measurements.append(variable);
}

void Manager::deleteVariable(int index){
    if (index < 0 || index > measurements.count())
        throw std::out_of_range("There is no column with this index");
    measurements.removeAt(index);
}
void Manager::addMeasurementRow(std::initializer_list<VariableData> list){
    for (auto & i : list){
        measurements.append(i);
    }
}
void Manager::removeMeasurementRow(int begin, int amount){
    measurements.remove(begin, amount);
}
void Manager::clearCalculated(){
    calculated.clear();
}
void Manager::addCalculated(VariableData & variable){
    calculated.append(variable);
}

Manager *Manager::instance()
{
    return GlobalManager;
}

void Manager::clear() {
    measurement_count = 0;
}







