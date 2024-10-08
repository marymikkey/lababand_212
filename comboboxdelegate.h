#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
  Q_OBJECT
 public:
  ComboBoxDelegate(QStringList options, QObject* parent = nullptr);
  ~ComboBoxDelegate();

  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option,
                        const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  void setModelData(QWidget* editor,
                    QAbstractItemModel* model,
                    const QModelIndex& index) const override;

 private:
  QStringList options;
};
#endif  // COMBOBOXDELEGATE_H
