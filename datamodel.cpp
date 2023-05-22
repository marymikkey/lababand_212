#include "datamodel.h"
#include "variable_data.h"
#include "manager.h"

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getMeasurementCount() + extraRows;
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVarCalcAmount();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int variable  = index.column();
    VariableData* v = Manager::instance()->getChoiceVarCalc(variable);

    if (v->measurements.size() <= row) return QVariant();

    if (role == Qt::DisplayRole)
    {
        QVariant r = QVariant(v->measurements[row]).toString();// + " ± " +
                    //QVariant(v->ierror(row)).toString();
        return r;
    }
    return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Vertical) return section + 1;

    VariableData* v = Manager::instance()->getChoiceVarCalc(section);

    return v->shortNaming;
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int variable = index.column();

    if (role == Qt::EditRole)
    {
        if (!value.canConvert<double>()) return false;
        VariableData* v = Manager::instance()->getChoiceVarCalc(variable);

        if (v->measurements.size() <= row)
        {
            v->measurements.append(value.toDouble());
            emit dataChanged(index, index);
            return true;
        }
        v->measurements[row] = value.toDouble();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (index.column() < Manager::instance()->getVariableSize())
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    else
        return QAbstractItemModel::flags(index);
}

void DataModel::insertColumn(int column)
{
    beginInsertColumns(QModelIndex(), column, column);
    endInsertColumns();
}

void DataModel::insertRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
    extraRows++;
}

