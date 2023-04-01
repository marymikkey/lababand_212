#include "VisualModel.h"
#include "Manager.h"


int VisualModel::rowCount(const QModelIndex & parent) const{
    return Manager::instance()->variables.size();
}
int VisualModel::columnCount(const QModelIndex & parent) const{
    return VariableData::Visual::OPTION_COUNT;
}
QVariant VisualModel::data(const QModelIndex & index, int role) const{
    int variable = index.row();
    int option = index.column();
    auto visual = Manager::instance()->variables[variable].visual;
    switch (role){
        case Qt::CheckStateRole:
            switch (option){
                case (0):
                    return visual.visible ? Qt::Checked : Qt::Unchecked;
            }
            return QVariant();

        case Qt::DisplayRole:
            switch(option){
                case(1):
                    return visual.width;
                case(2):
                    return visual.line_type;
                case(3):
                    return visual.point_type;
                case(4):
                    return visual.color;
                default:
                    return QVariant();
            }
        }
    return QVariant();
}

/*bool VisualModel::setData(const QModelIndex & index, const QVariant &value, int role){
    if(role == Qt::EditRole){
        if (!checkIndex(Index))
            return false;
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emitt a joined string
        QString result;
        for (int row = 0; row < ROWS; row++){
            for (int col = 0; col < COLS; col++)
                result += m_gridData[row][col] + ' ';
        }
        emit editCompleted(result);
        return true;
    }
    return false;
}
Qt::ItemFlags VisualModel::flags(const QModelIndex &index) const{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
*/

bool VisualModel::setData(const QModelIndex & index,const QVariant & value, int role){

    /*if (role == Qt::CheckStateRole){
        int variable = index.row();
        int option = index.column();
        auto& visual = Manager::instance()->(*variables)[variable].visual;
        if (option == 0){
            Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
            if (state == Qt::Checked){
                visual.visible = true;
            }
            else {
                visual.visible = false;
            }
            return true;
        }
    }

    if (role == Qt::EditRole){
        int variable = index.row();
        int option = index.column();
        auto & visual = Manager::instance()->(*variables)[variable].visual;
    }
    */



    int variable = index.row();
    int option = index.column();
    auto visual = Manager::instance()->variables[variable].visual;
    if (!checkIndex(index)){
        return false;
    }
    //save value from editor to member m_gridData

        switch (option){
            case (0):
                if (!value.canConvert<bool>()){
                    return false;
                }
                visual.visible = value.toBool();
                return true;
            case(1):
                if (!value.canConvert<int>()){
                    return false;
                }
                visual.width = value.toInt();
                return true;
            case(2):
                if (!value.canConvert<QString>()){
                    return false;
                }
                visual.line_type = value.toString();
                return true;
            case(3):
                if (!value.canConvert<QString>()){
                    return false;
                }
                visual.point_type = value.toString();
                return true;
            case(4):
                if (!value.canConvert<QString>()){
                    return false;
                }
                visual.color = value.toString();
                return true;
        return true;
        }

    return false;
}

Qt::ItemFlags VisualModel::flags(const QModelIndex &index) const{
    int option = index.column();
    if (option == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | QAbstractTableModel::flags(index);
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

