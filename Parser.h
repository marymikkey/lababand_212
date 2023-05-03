#ifndef PARSER_H
#define PARSER_H
#include <iomanip>
#include <stdexcept>
#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

template< class Parser, class Skipper, class ... Args>
void CanParce(std::string & str, const Parser & parser, const Skipper & skipper, Args && ...Args)
{
    std::string::const_iterator begin = str.begin(), end = str.end();
    qi::phrase_parse(begin,end,parser,skipper,std::forward<Args>(args) ...);
    if (begin!=end){
        std::cout << "Impossible to parse: " << std::quoted(std::string(begin,end)) << std::endl;
        throw std::runtime_error("Parse error");
    }
}



class AbsSyntaxTreeNode
{
public:
    virtual double evaluate() = 0;
    virtual ~AbsSyntaxTreeNode(){ }
};

using ASTN = AbsSyntaxTreeNode;

template<char Operator>
class OperatorNode : public ASTN
{
public:
    OperatorNode(ASTN * left, ASTN * right){
        this->left = left;
        this->right = right;
    }
    double evaluate(){
        //dskkkskdksk
    }
    ~OperatorNode(){
        delete left;
        delete right;
    }
private:
    ASTN * left;
    ASTN * right;
};

class ConstantNode : public ASTN
{
public:
    ConstantNode(double value):value(value){ }
    double evaluate(){
        return value;
    }
private:
    double value;
};



class AssignmentNode : public ASTN
{
public:
    AssignmentNode(std::string identifier, ASTN * & value): value(value), identifier(identifier){}
    double evaluate(){
        double val = value->evaluate();
        variable_map[identifier] = val;
        return val;
    }
private:
    std::string identifier;
    ASTN * value;
};

class FuncNode : public ASTN
{
public:
    FuncNode(std::string identifier, QList<ASTN*> & values : values(values), identifier(identifier){}
    double evaluate(){
        double val = values[0]->evaluate();
        if (identifier == "sqrt")
            return sqrt(val);
        else if (identifier == "square")
            return val*val;
        std::cout << "Unknown function: " << std::quoted(identifier) << std::endl;
        throw std::runtime_error("Parse error");
    }
private:
    std::string identifier;
    QList<ASTN*> values;
};

#endif // PARSER_H
