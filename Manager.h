#ifndef MANAGER_H
#define MANAGER_H
#include "VariableData.h"
#include <initializer_list>



class Manager {
    public:
        /*Manager(QList<VariableData> * variables = nullptr, QList<VariableData> * calculated = nullptr){
            this -> variables = new QList<VariableData>;
            this -> calculated = new QList<VariableData>;
            this -> variables = variables;
            this -> calculated = calculated;
        }
        ~Manager(){
            delete[] variables;
            delete[] calculated;
        }*/
        void addVariable(const VariableData &);
        void deleteVariable(int);
        void addMeasurementRow(std::initializer_list<VariableData> list);
        void removeMeasurementRow(int begin, int amount);
        void clearCalculated();
        void addCalculated(VariableData &);
        int GetVariableSize() const {return variables.size();};



        static Manager * instance();

        QList<VariableData> variables;
        QList<VariableData> calculated;
};


#endif // MANAGER_H
