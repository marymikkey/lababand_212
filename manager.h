
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
        void removeMeasurementRow(int begin, int amount);
        void clearCalculated();
        void addCalculated(VariableData &);
        int GetVariableSize() const {return measurements.size();};
        void clear();
        static Manager* instance();

        Plot *plot;

        QList<VariableData> measurements;
        QList<VariableData> calculated;
        int measurement_count = 0;
};

#endif // MANAGER_H
