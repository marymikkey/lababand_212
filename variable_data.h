#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QMap>
#include <QList>
#include <QString>
#include <utility>
#include <QColor>
#include "qcustomplot.h"

class VariableData
{
public:
    QList<double> measurements;
    QList<double> calcErrors;
    QString fullNaming;
    QString shortNaming;
    QList <double> values;

    struct VisualOptions
    {
        bool visible = true;
        int width = 3;
        Qt::PenStyle line_type = Qt::SolidLine;
        QCPScatterStyle::ScatterShape point_type = QCPScatterStyle::ScatterShape::ssNone;
        QColor color = "darkCyan";
//        QColor color1 = "darkGreen";

        static QMap<Qt::PenStyle, QString> line_types;
        static QMap<QCPScatterStyle::ScatterShape, QString> point_types;

        static constexpr int FIELDS = 5;
    } visual;

    struct Naming
    {
        QString full;
        QString alias;
        static constexpr int FIELDS = 2;
    }naming;

    struct Error
    {
        enum Type
        {
            Absolute,
            Relative,
            CalculatedValue,
        } type = Type::Absolute;
        double value = 0.1;
        static QMap<VariableData::Error::Type, QString> error_types; //static QMap<Type, QString> error_types;
        static constexpr int FIELDS = 2;

    }error;

    double ierror(int index = 0);
    int getMeasurementsCount();
    VariableData(QString fullNaming, QString shortNaming = "",
                 QList<double> measurements = QList<double> {}, QList<double> calcErrors = QList<double> {});
    VariableData();
    VariableData(int size);
    double getError(int measurement) const;

};

#endif // VARIABLEDATA_H
