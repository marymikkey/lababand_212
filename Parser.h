#ifndef PARSER_H
#define PARSER_H
#include <iomanip>
#include <stdexcept>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <QApplication>
namespace qi = boost::spirit::qi;

template< class Parser, class Skipper, class ... Args>
void CanParce(std::string & str, const Parser & parser, const Skipper & skipper, Args && ...args)
{
    std::string::const_iterator begin = str.begin(), end = str.end();
    qi::phrase_parse(begin,end,parser,skipper,std::forward<Args>(args) ...);
    if (begin!=end){
        std::cout << "Impossible to parse: " << std::quoted(std::string(begin,end)) << std::endl;
        throw std::runtime_error("Parse error");
    }
}



class AbstractSyntaxTreeNode
{
public:
    virtual double evaluate() = 0;
    virtual ~AbstractSyntaxTreeNode(){ }
};

using ASTN = AbstractSyntaxTreeNode;



template<char Operator>
class OperatorNode : public ASTN
{
public:
    OperatorNode(ASTN * left, ASTN * right){
        this->left = left;
        this->right = right;
    }
    double evaluate(){
        if (Operator == '+')
            return left->evaluate() + right->evaluate();
        else if (Operator == '*')
            return left->evaluate() * right->evaluate();
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


class ArgumentsNode : public ASTN
{
public:
    ArgumentsNode(const ASTN* a, const ASTN* b): a(a), b(b){}
    double evaluate(){
        return a->evaluate();
    }
private:
    ASTN * a;
    ASTN * b;
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
    FuncNode(std::string identifier, QList<ASTN*> & values) : values(values), identifier(identifier){}
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

class VariableNode : public ASTN
{
public:
    VariableNode(std::string identifier) : identifier(identifier){}
    double evaluate(){
        return variable_map[identifier];
    }
private:
    std::string identifier;
};


#endif // PARSER_H
