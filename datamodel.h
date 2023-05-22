#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "variable_data.h"

class DataModel : public QAbstractTableModel
{
 public:
  DataModel(QObject* parent = nullptr) : QAbstractTableModel(parent){}
  ~DataModel(){};

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
  void insertColumn(int column);
  void insertRow(int row);
private:
  int extraRows = 0;
};


#endif // DATAMODEL_H
