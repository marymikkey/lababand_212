#include "Parser.h"


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
QVariant OperatorNode<Operator>::evaluate(){
    qInfo() << "OperatorNode " << Operator << " " << left << " " << right << " " << this << Qt::endl;
    QList<QVariant> l = left->evaluate().toList();
    QList<QVariant> r = right->evaluate().toList();
    if (Operator == '+')
        return ApplyVectorOperation(l,r,[](double a, double b){return a + b;});
    else if (Operator == '-')
        return ApplyVectorOperation(l,r,[](double a, double b){return a - b;});
    else if (Operator == '*')
        return ApplyVectorOperation(l,r,[](double a, double b){return a * b;});
    else if (Operator == '/'){
        if (r!=0){
            return ApplyVectorOperation(l,r,[](double a, double b){return a / b;});
        }
        else{
        std::cout << "Zero Division";
        throw std::runtime_error("Calculation error");
        }
    }
}

QVariant ConstantNode::evaluate(){
    qInfo() << "ConstantNode " << value << " " << this << Qt::endl;
    //qInfo() << value;
    return QList<QVariant>(std::initializer_list<QVariant>{value});
}

QVariant ArgumentsNode::evaluate(){
    qInfo() << "ArgumentsNode " << a << " " << b << " " << this << Qt::endl;
    QVariant av = a->evaluate(), bv = b->evaluate();
    return QList<QVariant>({av}) + bv.toList();
}

QVariant AssignmentNode::evaluate(){
    qInfo() << "AssignmentNode " << identifier << " " << value << " " << this << Qt::endl;
    QList<QVariant> val = (value->evaluate()).toList();
    variable_map[identifier] = val;
    return variable_map[identifier];
}

QVariant FunctionNode::evaluate(){
        qInfo() << "FunctionNode " << identifier << " " << values << " " << this << Qt::endl;
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

QVariant EmptyNode::evaluate(){
        qInfo() << "EmptyNode " << this << Qt::endl;
       return QList<QVariant>();
    }

QVariant VariableNode::evaluate(){
        qInfo() << "VariableNode " << identifier << " " << this  << Qt::endl;
        return variable_map[identifier];
    }

ArithmeticGrammar1::ArithmeticGrammar1() : ArithmeticGrammar1::base_type(start){
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














