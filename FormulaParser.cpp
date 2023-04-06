#include "FormulaParser.h"

namespace qi = boost::spirit::qi;


std::vector<QString> FormulaParser::desintegratingParcer(QString input)
{
    std::vector<QString> vect;

    for (int i = 0; i < input.size(); ++i){
        QString out_string;


        qi::parse(
            input.begin()+i, input.begin()+i+1,
            qi::int_,
            out_string);
            vect.push_back(out_string);

    }
    return vect;
}


double FormulaParser::parce(){
    double result = computeExpression();
    if (position != tokens_size)
        throw std::lenght_error("Error in expression at " + (tokens[position]).toStdString());
    return result;
}

double FormulaParser::computeDigit(){
    double result;
    QString element = tokens[position];

    if (element == "("){
        ++position;
        result = computeExpression();
        QString closingBracket;
        if (position < tokens_size)
            closingBracket = tokens[position];
        else
            throw std::domain_error("Unexpected end of expression");

        if (position < tokens_size && closingBracket == ")"){
            ++position;
            return result;
        }
        QString message = "expected '(' but got '" + closingBracket + "'";
        throw std::domain_error(message.toStdString());
    }
    ++position;

    return element.toDouble();
}

double FormulaParser::computeMultiplication(){
    double first = computeDigit();
    while (position < tokens_size){
        QString operation = tokens[position];
        if (!(operation == "*") && !(operation == "/"))
            break;
        else
            ++position;

        double second = computeDigit();

        if (operation == "*")
            first *= second;
        else
            first /= second;
    }
    return first;
}



double FormulaParser::computeExpression(){
    double first = computeMultiplication();

    while (position < tokens_size){
        QString operation = tokens[position];
        if (!(operation == "+") && !(operation=="-"))
            break;
        else
            ++position;
        double second = computeMultiplication();
        if (operation == "+")
            first += second;
        else
            first -= second;
    }
    return first;
}
