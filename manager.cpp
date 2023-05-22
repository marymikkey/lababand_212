#include "manager.h"
#include <QGlobalStatic>

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

VariableData* Manager::getVariable(QString alias, bool useAlias){
    for (auto& v: variables){
        if (useAlias)
        {
         if (v.naming.alias == alias)
            {
                return &v;
            }
        }
        else
        {
            if (v.naming.full == alias)
            {
                return &v;
            }
        }
    }
    return nullptr;
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

int Manager::getVariableSize() const{
    return variables.size() + calculated.size();
    //return variables.size();
}

int Manager::getMeasurementCount() const{
    int max = 0;
    for (auto& v: variables) max = (v.values.size() > max) ? v.values.size() : max;
    for (auto& v: calculated) max = (v.values.size() > max) ? v.values.size() : max;
    return max;
    //return measurement_count;
}

void Manager::addMeasurement()
{
    int size = getMeasurementCount();
    for (auto& v: variables) v.values.append(0);
//            resize(size + 1);
    for (auto& v: variables) v.values[size] = size + 0.5;
}

void Manager::removeMeasurement()
{
    int size = getMeasurementCount();
    if (size==0) return;
    for (auto& v:variables) v.values.removeLast();
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

VariableData* Manager::getVariable(const QString& name)
{
    for (auto& v: variables)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    return nullptr;
}

VariableData* Manager::getVariable(int index)
{
    if (index >= variables.size()) throw std::runtime_error("No such index (in getVariable(int index))");
    return &variables[index];
}

VariableData* Manager::getCalculated(const QString& name)
{
    for (auto& v: calculated)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    throw std::runtime_error("No such index (in getCalculated(const QString& name))");
}

VariableData* Manager::getCalculated(int index)
{
    if (index >= variables.size()) throw std::runtime_error("No such index (in getCalculated(int index))");
    return &calculated[index];
}


int Manager::getVarCalcAmount() {
    return this->getCalculatedSize() + this->getVariableSize();
}

VariableData* Manager::getChoiceVarCalc(int index)
{
    if (index >= getVarCalcAmount()) throw std::runtime_error("No such index (in getChoiceVarCalc(int index))");
    if (index < getVariableSize()) return getVariable(index);
    else return getCalculated(index - getVariableSize());
}

VariableData* Manager::getChoiceVarCalc(const QString& name)
{
    for (auto& v: variables)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    for (auto& v: calculated)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    return nullptr;
}

void Manager::clear() {
    measurement_count = 0;
    variables.clear();
    calculated.clear();
}







