
#ifndef MANAGER_H
#define MANAGER_H
#include "variable_data.h"
#include <initializer_list>
#include "plots/plot.h"
#include <QGlobalStatic>


class Manager {
    public:
        void addVariable(const VariableData &);
        void deleteVariable(int);
        void addMeasurementRow(std::initializer_list<VariableData> list);
        void addMeasurementRow(QList<double> data);
        void removeMeasurementRow(int row);
        void clearCalculated();
        void addCalculated(VariableData & var);
        inline int getVariablesSize() const {return variables.size();};
        inline int getMeasurementAmount() const {return measurement_count;}
        void clear();
        void recalcMeasurementAmount();
        int getCalculatedSize();
        static Manager* instance();

        Plot *plot;

        QList<VariableData> variables;
        QList<VariableData> calculated;
        int measurement_count = 0;
};

#endif // MANAGER_H
