#include "FormulaParser.h"

namespace qi = boost::spirit::qi;




std::vector<std::string> FormulaParser::desintegratingParcer(std::string input)
{
    std::vector<std::string> vect;

    for (size_t i = 0; i < input.size(); ++i){
        std::string out_string;


        qi::parse(   input.begin()+i,  input.begin()+i+1,   qi::int_,   out_string   );
        vect.push_back(out_string);

    }
    return vect;
}


double FormulaParser::parce(){
    double result = computeExpression();
    if (position != tokens_size)
        throw std::length_error("Error in expression at " + (tokens[position]));
    return result;
}

double FormulaParser::computeDigit(){
    double result;
    std::string element = tokens[position];

    if (element == "("){
        ++position;
        result = computeExpression();
        std::string closingBracket;
        if (position < tokens_size)
            closingBracket = tokens[position];
        else
            throw std::domain_error("Unexpected end of expression");

        if (position < tokens_size && closingBracket == ")"){
            ++position;
            return result;
        }
        std::string message = "expected '(' but got '" + closingBracket + "'";
        throw std::domain_error(message);
    }
    ++position;

    return std::stod(element);
}

double FormulaParser::computeMultiplication(){
    double first = computeFunction();
    while (position < tokens_size){
        std::string operation = tokens[position];
        if (!(operation == "*") && !(operation == "/"))
            break;
        else
            ++position;

        double second = computeFunction();

        if (operation == "*")
            first *= second;
        else
            first /= second;
    }
    return first;
}

double FormulaParser::computeFunction(){
    while (position < tokens_size){
        std::string func_name = tokens[position];
        __try {
            std::stod(tokens[position])
        }
        __except ( /* filter expression */ ) {
        }
    }






    double first = computeDigit();

    while (position < tokens_size){
        std::string operation = tokens[position];
        if (!(operation == "+") && !(operation=="-"))
            break;
        else
            ++position;
        double second = computeDigit();
        if (operation == "+")
            first += second;
        else
            first -= second;
    }
    return first;
}


double FormulaParser::computeExpression(){
    double first = computeMultiplication();

    while (position < tokens_size){
        std::string operation = tokens[position];
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

class FuncNode : public ASTN
{
public:
    FuncNode(std::string identifier, QList<ASTN*> & values : values(values), identifier(identifier){}
    double evaluate(){
        auto vs = values[0]->evaluate().toList();
        if (identifier == "sqrt")
            return sqrt(vs[0].toDouble());
        else if (identifier == "square")
            return vs[0].toDouble()*vs[0].toDouble();
        else if (identifier == "min"){
            double ret = vs[0].toDouble();
            for (auto & v: vs)
                ret = std::min(v.toDouble(),ret);
                return ret;
        }
        std::cout << "Unknown function: " << std::quoted(identifier) << std::endl;
        throw std::runtime_error("Parse error");
    }
private:
    std::string identifier;
    QList<ASTN*> values;
};

