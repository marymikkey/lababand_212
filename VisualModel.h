#ifndef VISUALMODEL_H
#define VISUALMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "VariableData.h"
#include "Manager.h"

class VisualModel : public QAbstractTableModel {
    public:
        VisualModel(QObject* parent = nullptr) : QAbstractTableModel(parent){
        };
        ~VisualModel(){};

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index,
                    int role = Qt::DisplayRole) const override;

        QVariant headerData(int section,
                          Qt::Orientation orientation,
                          int role = Qt::DisplayRole) const override;

        bool setData(const QModelIndex& index,
                   const QVariant& value,
                   int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;

};

#endif  // VISUALMODEL_H


