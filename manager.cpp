#include "Manager.h"
#include <QGlobalStatic>
#include "Manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::recalcMeasurementAmount() {
    measurement_count = 0;
    for (int i = 0; i < this->getVariablesSize(); ++i)
        if (variables.at(i).measurements.size() > measurement_count)
            measurement_count = variables.at(i).measurements.size();
    for (int i = 0; i < this->getCalculatedSize(); ++i)
        if (calculated.at(i).measurements.size() > measurement_count)
            measurement_count = calculated.at(i).measurements.size();
}



void Manager::addVariable(const VariableData & variable){
    variables.append(variable);
    Manager::instance()->recalcMeasurementAmount();
}

void Manager::deleteVariable(int index){
    if (index < 0 || index > variables.count())
        throw std::out_of_range("There is no column with this index");
    variables.removeAt(index);
    Manager::instance()->recalcMeasurementAmount();
}
void Manager::addMeasurementRow(std::initializer_list<VariableData> list){
    for (auto & i : list){
        variables.append(i);
    }
    Manager::instance()->recalcMeasurementAmount();
}
void Manager::addMeasurementRow(QList<double> data){
    for (auto & i : data){
        variables.append(i);
    }
    Manager::instance()->recalcMeasurementAmount();
}

int Manager::getCalculatedSize(){
    return calculated.size();
}



void Manager::removeMeasurementRow(int row){
    if (row < 0 || row >= measurement_count)
        throw std::out_of_range("This row doesn't exist");
    for (int i = 0; i < variables.count(); ++i)
        if (variables[i].measurements.count() > row)
            variables[i].measurements.removeAt(row);
    Manager::instance()->recalcMeasurementAmount();
}
void Manager::clearCalculated(){
    calculated.clear();
    Manager::instance()->recalcMeasurementAmount();
}
void Manager::addCalculated(VariableData & variable){
    calculated.append(variable);
    Manager::instance()->recalcMeasurementAmount();
}

Manager *Manager::instance()
{
    return GlobalManager;
}

void Manager::clear() {
    measurement_count = 0;
    variables.clear();
    calculated.clear();
}







