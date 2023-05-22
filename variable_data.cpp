#include "variable_data.h"

QMap<Qt::PenStyle, QString> VariableData::VisualOptions::line_types = {
    {Qt::SolidLine, "Solid"},
    {Qt::DashLine, "Dashed"},
    {Qt::DotLine, "Dotted"},
};

QMap<QCPScatterStyle::ScatterShape, QString> VariableData::VisualOptions::point_types = {
    {QCPScatterStyle::ScatterShape::ssNone, "None"},
    {QCPScatterStyle::ScatterShape::ssCross, "Cross"},
    {QCPScatterStyle::ScatterShape::ssCircle, "Circle"},
};

QMap<VariableData::Error::Type, QString> VariableData::Error::error_types = {
    {VariableData::Error::Type::Relative, "Relative"},
    {VariableData::Error::Type::Absolute, "Absolute"},
    {VariableData::Error::Type::CalculatedValue, "Calculated"},
};

int VariableData::getMeasurementsCount() {return measurements.size();}

VariableData::VariableData(QString shortNaming, QString fullNaming, QList<double> meas, QList<double> calcErrors)
    :   measurements { meas }, calcErrors{ calcErrors },  fullNaming { fullNaming },  shortNaming { shortNaming }
{
    if (!calcErrors.empty())
        error.type = Error::Type::CalculatedValue;
}

VariableData::VariableData(int size)
{
    for (int i = 0; i < size; ++i) measurements.append(0);

    QVariant t = QVariant(rand() % 10);
    shortNaming = t.toString();
    fullNaming = QString("New") + t.toString();
}
VariableData::VariableData()
{
    QString alias;
    auto generator = QRandomGenerator::global();
    for (int i = 0; i < 5; ++i)
        alias.append(QChar('a'+(generator->generate()% 26)));

    naming.alias = alias;
    naming.full = QString("Variable ") + alias.toUpper();
}
double VariableData::getError(int measurement) const
{
    switch(error.type)
    {
        case Error::Type::Absolute:
            return error.value;
        case Error::Type::Relative:
            return error.value * values[measurement];
        case Error::Type::CalculatedValue:
            throw "Calculated variables not yet implemented";
    }
}

double VariableData::ierror(int index)
{
    switch(int(VariableData::error.type))
    {
    case Error::Type::Relative:
            return VariableData::error.value * VariableData::measurements.at(index);
    case Error::Type::Absolute:
            return VariableData::error.value;
    case Error::Type::CalculatedValue:
            //return calcErrors.at(index);
            return VariableData::error.value;
    default:
            throw "Uncorrected Type of Error";
    }

}
