#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H
#include <QApplication>
#include <iostream>
#include <QList>
#include <QString>
#include <utility>

//enum class ErrorType{ Mean, MeanSquare};
class VariableData {
    public:
        struct Visual{
            static constexpr int OPTION_VISIBLE= 0;
            bool visible = true;
            static constexpr int OPTION_COUNT = 5;
            int width = 1;
            QString line_type = "solid";
            QString point_type = "square";
            QString color = "black";



            /*bool Visible = true;
            int width = 1;
            QString line_type = "solid";
            QString point_type = "square";
            QString color = "black";
            static constexpr int OPTION_COUNT = 5;
            */

        } visual;
        /*VariableData(QList<double> * measurements, QString naming, ErrorType instrument, QList<double> * err = nullptr){
            this -> measurements = new QList<double>[(*measurements).size()];
            this -> measurements = measurements;
            this -> naming = naming;
            this -> instrument = instrument;
            this -> err = new QList<double>[(*err).size()];
            this -> err = err;
            m_error_size = (*err).size();
            m_measurements_size = (*measurements).size();
        }
        ~VariableData(){
            delete[] measurements;
            delete[] err;
        }
        double error(int measurement){
            return (*err)[measurement];
        }
        int getErrorSize(){
            return m_error_size;
        }
        int getMeasurementSize(){
            return m_measurements_size;
        }

    public:
        QList<double> * measurements;
        QString naming;
        ErrorType instrument;
        QList<double> * err;
        int m_error_size;
        int m_measurements_size;
        */

};



#endif // VARIABLEDATA_H
