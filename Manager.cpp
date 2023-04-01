#include "Manager.h"
#include <QGlobalStatic>
#include "Manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::addVariable(const VariableData & variable){
    variables.append(variable);
}

void Manager::deleteVariable(int index){
    if (index < 0 || index > variables.count())
        throw std::out_of_range("There is no column with this index");
    variables.removeAt(index);
}
void Manager::addMeasurementRow(std::initializer_list<VariableData> list){
    for (auto i : list){
        variables.append(i);
    }
}
void Manager::removeMeasurementRow(int begin, int amount){
    variables.remove(begin, amount);
}
void Manager::clearCalculated(){
    calculated.clear();
}
void Manager::addCalculated(VariableData & variable){
    calculated.append(variable);
}

static Manager * instance(){
    return new Manager();
}
