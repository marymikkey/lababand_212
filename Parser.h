#ifndef PARSER_H
#define PARSER_H
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <QApplication>
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;
//extern std::map<std::string, QVariant> variable_map;
//QList<QPair<double,double>> vect;
//std::map<std::string, QVariant> variable_map;
extern std::map<std::string, QVariant> variable_map;

template<class Parser, class Skipper, class ... Args>
void ParseOrDie(const std::string & input, const Parser & parser, const Skipper & skipper, Args && ...args)
{
    std::string::const_iterator begin = input.begin(), end = input.end();
    qi::phrase_parse(begin,end,parser,skipper,std::forward<Args>(args) ...);
    if (begin != end){
        std::cout << "Impossible to parse: " << std::quoted(std::string(begin,end)) << std::endl;
        throw std::runtime_error("Parse error");
    }
}

QVariant ApplyVectorOperation(QList<QVariant> & l, QList<QVariant> & r, double (*f)(double, double));

class AbstractSyntaxTreeNode
{
public:
    virtual QVariant evaluate() = 0;
    virtual ~AbstractSyntaxTreeNode(){ }
};

using ASTN = AbstractSyntaxTreeNode;
using ASTNPtr = AbstractSyntaxTreeNode *;

template<char Operator>
class OperatorNode : public ASTN
{
public:
    OperatorNode(const ASTNPtr& left, const ASTNPtr& right) : left(left), right(right){ }
    QVariant evaluate();
    ~OperatorNode() {
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
    QVariant evaluate();
private:
    double value;
};

class ArgumentsNode : public ASTN
{
public:
    ArgumentsNode(ASTNPtr& a, ASTNPtr& b): a(a), b(b){}
    QVariant evaluate();
private:
    ASTNPtr a,b;
};

class AssignmentNode : public ASTN
{
public:
    AssignmentNode(std::string identifier, const ASTNPtr & value): identifier(identifier), value(value){}
    QVariant evaluate();
private:
    std::string identifier;
    ASTN * value;
};

class FunctionNode : public ASTN
{
public:
    FunctionNode(std::string identifier, const ASTNPtr & values) : identifier(identifier), values(values){}

    QVariant evaluate();
private:
    std::string identifier;
    ASTN * values;
};

class EmptyNode : public ASTN
{
public:
    EmptyNode(){ }
    QVariant evaluate();
};

class VariableNode : public ASTN
{
public:
    VariableNode(std::string identifier) : identifier(identifier){}
    QVariant evaluate();
private:
    std::string identifier;
};


class ArithmeticGrammar1 : public qi::grammar<std::string::const_iterator, ASTNPtr (), qi::space_type>
{
public:
    using Iterator = std::string::const_iterator;

    ArithmeticGrammar1();

    qi::rule<Iterator, std::string(), qi::space_type> varname;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> start, term, group, product, factor;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> constant, variable;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> function, args;
};




#endif // PARSER_H
