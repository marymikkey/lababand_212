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

extern std::map<std::string, QVariant> variable_map;

void test1(QString input);


#endif // PARSER_H
