#include "Grammar.h"
#include <QDebug>

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <QApplication>
namespace qi = boost::spirit::qi;

//extern std::map<std::string, QVariant> variable_map;
//QList<QPair<double,double>> vect;
std::map<std::string, QVariant> variable_map;
//extern std::map<std::string, QVariant> variable_map;



template< class Parser, class Skipper, class ... Args>
void ParseOrDie(const std::string & input, const Parser & parser, const Skipper & skipper, Args && ...args)
{
    std::string::const_iterator begin = input.begin(), end = input.end();
    qi::phrase_parse(begin,end,parser,skipper,std::forward<Args>(args) ...);
    if (begin != end){
        std::cout << "Impossible to parse: " << std::quoted(std::string(begin,end)) << std::endl;
        throw std::runtime_error("Parse error");
    }
}

//еще вектора в парах. погрешность

class AbstractSyntaxTreeNode
{
public:
    virtual QVariant evaluate() = 0;
    virtual ~AbstractSyntaxTreeNode(){ }
};

using ASTN = AbstractSyntaxTreeNode;
using ASTNPtr = AbstractSyntaxTreeNode *;

QVariant ApplyVectorOperation(QList<QVariant> & l, QList<QVariant> & r, double (*f)(double, double)){
    QList<QVariant> result;
    if (l.size() == 1){
        for (QVariant & elem : r){
            result.append(f(l[0].toDouble(), elem.toDouble()));
        }
    }
    else if (r.size() == 1){
        for (QVariant & elem : l){
            result.append(f(elem.toDouble(), r[0].toDouble()));
        }
    }
    else if (l.size() == r.size()){
        for (int i = 0; i < r.size(); ++i){
            result.append(f(l[i].toDouble(), r[i].toDouble()));
        }
    }
    else{
        std::cout << "Vectors of different length detected: " << l.size() << " and " << r.size() << std::endl;
        throw std::runtime_error("Calculation error");
    }
    return result;
}






template<char Operator>
class OperatorNode : public ASTN
{
public:
    OperatorNode(const ASTNPtr& left, const ASTNPtr& right) : left(left), right(right){ }
    QVariant evaluate(){
        QList<QVariant> l = left->evaluate().toList();
        QList<QVariant> r = right->evaluate().toList();
        if (Operator == '+')
            return ApplyVectorOperation(l,r,[](double a, double b){return a + b;});
        else if (Operator == '-')
            return ApplyVectorOperation(l,r,[](double a, double b){return a - b;});
        else if (Operator == '*')
            return ApplyVectorOperation(l,r,[](double a, double b){return a * b;});
        //        else if (Operator == '/'){
        //            if (r!=0){
        //                return ApplyVectorOperation(l,r,[](double a, double b){return a / b;});
        //            }
        //            else{
        //            std::cout << "Zero Division";
        //            throw std::runtime_error("Calculation error");
        //            }
        //        }
    }
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
    QVariant evaluate(){
        //qInfo() << value;
        return value;
    }
private:
    double value;
};


class ArgumentsNode : public ASTN
{
public:
    ArgumentsNode(ASTNPtr& a, ASTNPtr& b): a(a), b(b){}
    QVariant evaluate(){
        QVariant av = a->evaluate(), bv = b->evaluate();
        return QList<QVariant>({av}) + bv.toList();
    }
private:
    ASTNPtr a,b;
};



class AssignmentNode : public ASTN
{
public:
    AssignmentNode(std::string identifier, const ASTNPtr & value): identifier(identifier), value(value){}
    QVariant evaluate(){
        QList<QVariant> val = (value->evaluate()).toList();
        variable_map[identifier] = val;
        return variable_map[identifier];
    }
private:
    std::string identifier;
    ASTN * value;
};

class FunctionNode : public ASTN
{
public:
    FunctionNode(std::string identifier, const ASTNPtr & values) : identifier(identifier), values(values){}

    QVariant evaluate(){
        auto vs = values->evaluate().toList();
        if (identifier == "one")
            return 1;
        if (identifier == "sqrt")
            return sqrt(vs[0].toDouble());
        else if (identifier == "square")
            return vs[0].toDouble()*vs[0].toDouble();
        else if (identifier == "min"){
            double ret = vs[0].toDouble();
            for (auto & v: vs){
                ret = std::min(v.toDouble(),ret);
            }
            return ret;
        }

        std::cout << "Unknown function: " << std::quoted(identifier) << std::endl;
        throw std::runtime_error("Evaluate error");
    }
private:
    std::string identifier;
    ASTN * values;
};

class EmptyNode : public ASTN
{
public:
    EmptyNode(){ }
    QVariant evaluate(){
        return QList<QVariant>();
    }
};

class VariableNode : public ASTN
{
public:
    VariableNode(std::string identifier) : identifier(identifier){}
    QVariant evaluate(){
        return variable_map[identifier];
    }
private:
    std::string identifier;
};

namespace phx = boost::phoenix;

class ArithmeticGrammar1 : public qi::grammar<std::string::const_iterator, ASTNPtr (), qi::space_type>
{
public:
    using Iterator = std::string::const_iterator;

    ArithmeticGrammar1() : ArithmeticGrammar1::base_type(start)
    {
        varname %= qi::alpha >> *qi::alnum;
        start = (varname >> '=' >> term)
                    [qi::_val = phx::new_<AssignmentNode>(qi::_1,qi::_2)] |
                term [qi::_val = qi::_1];

        term = (product >> '+' >> term)
                   [qi::_val = phx::new_<OperatorNode<'+'>>(qi::_1, qi::_2)] |
               product [qi::_val = qi::_1];

        product = (factor >> '*' >> term)
                      [qi::_val = phx::new_<OperatorNode<'*'>>(qi::_1, qi::_2)] |
                  factor [qi::_val = qi::_1];

        factor = group [qi::_val = qi::_1] |
                 function [qi::_val = qi::_1] |
                 variable [qi::_val = qi::_1] |
                 constant [qi::_val = qi::_1];

        function = (varname >> '(' >> args >> ')')[qi::_val = phx::new_<FunctionNode>(qi::_1,qi::_2)];
        args = (term >> ',' >> args)[qi::_val = phx::new_<ArgumentsNode>(qi::_1, qi::_2)]; // |;
            //term [qi::_val = phx::new_<ArgumentsNode>(qi::_1)];

        constant = qi::double_ [qi::_val = phx::new_<ConstantNode>(qi::_1)];
        variable = varname [qi::_val = phx::new_<VariableNode>(qi::_1)];
        group %= '(' >> term >> ')';
    }

    qi::rule<Iterator, std::string(), qi::space_type> varname;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> start, term, group, product, factor;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> constant, variable;
    qi::rule<Iterator, ASTNPtr(), qi::space_type> function, args;
};

void test1(QString input){
    try {
        ASTNPtr out_node;
        ParseOrDie(input.toStdString(), ArithmeticGrammar1(), qi::space, out_node);
        qInfo() << "evaluate() = " << out_node->evaluate();
        delete out_node;
    } catch (std::exception& e){
        qInfo() << "EXCEPTION: " << e.what();
    }
}
