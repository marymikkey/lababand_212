#include "Grammar.h"
#include "Manager.h"
#include "Parser.h"

class ArithmeticGrammar1 : public qi::grammar<std::string::const_iterator, ASTN * (), qi::space_type>
{
public:
    using Iterator = std::string::const_iterator;

    ArithmeticGrammar1() : ArithmeticGrammar1::base_type(start)
    {
        varname %= qi::alpha >> *qi::alnum;
        start = (varname >> '+' >> term)
                [qi::val = phx::new_<AssignmentNode>(qi::_1,qi::_2)] |
                term [qi::+val = qi::_1];

        term = (product >> '+' >> term)
                [qi::_val = phx::new_<OperatorNode<'+'>>(qi::_1, qi::_2)] |
                product [qi::_val = qi::_1];

        product = (factor >> '*' >> term)
                [qi::_val = phx::new_<OperatorNode<'*'>>(qi::_1, qi::_2)] |
                factor [qi::_val = qi::_1];

        factor = group [qi::_val = qi::_1] |
        variable [qi::_val = qi::_1] |
        constant [qi::_val = qi::_1];

        function = (varname >> '(' >> args >> ')')[qi::_val = phx::new_<FuncNode>(qi::_1,qi::_2)];
        args = (term >> ',' >> args)[qi::_val = qi::_1] |
                term [qi::_val = phx::new_<QList<double>>(qi::_1)];

        constant = qi::double_ [qi::_val = phx::new_<ConstantNode>(qi::_1)];
        variable = varname [qi::_val = phx::new_<VariableNode>(qi::_1)];
        group %= '(' >> term >> ')';
    }

    qi::rule<Iterator, std::string(), qi::space_type> varname;
    qi::rule<Iterator, ASTN*(), qi::space_type> start, term, group, product, factor;
    qi::rule<Iterator, ASTN*(), qi::space_type> constant, variable;
    qi::rule<Iterator, ASTN*(), qi::space_type> function, args;
};
