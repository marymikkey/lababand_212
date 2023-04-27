#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <QApplication>
#include <boost/spirit/include/qi.hpp>
#include "Manager.h"
#include <exception>
#include <<boost/numeric/conversion/cast.hpp>
namespace qi = boost::spirit::qi;


class FormulaParser{
public:
    FormulaParser(QString code = "" /*, std::vector<QString> & tokens = {}*/){
        this -> code = code;
        tokens = desintegratingParcer(code);
        int tokens_size = boost::numeric_cast<int>(tokens.size());
    }
    ~FormulaParser();
    void setManager();
    double parce();
    std::vector<QString> desintegratingParcer(QString input);
    double computeExpression();
    double computeMultiplication();
    double computeDigit();

private:
    QString code;
    std::vector<QString> tokens;
    int position;
    int tokens_size;
protected:
    Manager p_manager;
};



#endif // FORMULAPARSER_H
