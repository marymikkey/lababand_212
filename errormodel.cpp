#include "errormodel.h"
#include "variable_data.h"
#include "manager.h"

int ErrorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVarCalcAmount();
}

int ErrorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return VariableData::Error::FIELDS;
}

QVariant ErrorModel::data(const QModelIndex &index, int role) const
{
    int variable = index.row();
    int option  = index.column();
    auto& instrument = Manager::instance() -> getChoiceVarCalc(variable)->error;

    switch (role)
    {
        case Qt::DisplayRole:
            switch (option)
            {
              case 0:
                return instrument.error_types.value(instrument.type);
              case 1:
                return instrument.value;
            }
    }
    return QVariant();
}

bool ErrorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    auto& instrument = Manager::instance() -> getChoiceVarCalc(variable)->error;

    if (role == Qt::EditRole)
    {
        switch (option)
        {
          case 0:
            instrument.type = VariableData::Error::error_types.key(value.toString());
            emit dataChanged(index, index);
            return true;
          case 1:
            instrument.value = value.toDouble();
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant ErrorModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if( orientation == Qt::Vertical )
    {
        return QString(Manager::instance() -> getChoiceVarCalc(section)->shortNaming);
    }

    switch( section )
    {
    case 0:
        return QString( "type" );
    case 1:
        return QString( "value" );
    }
    return QVariant();
}

Qt::ItemFlags ErrorModel::flags(const QModelIndex &index) const
{
    if (index.row() < Manager::instance()->getVariableSize())
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    else
        return QAbstractItemModel::flags(index);
}

void ErrorModel::insertRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
}
