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
        };
};


#endif // VARIABLEDATA_H
