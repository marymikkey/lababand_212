#include "colordelegate.h"

#include <QColor>
#include <QColorDialog>

ColorDelegate::ColorDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

ColorDelegate::~ColorDelegate()
{
}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return new QColorDialog(parent);
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QColorDialog * color_dialog = static_cast<QColorDialog *>(editor);
    QColor color = index.model()->data(index, Qt::BackgroundRole).toString();
    color_dialog->setCurrentColor(color);
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QColorDialog * color_dialog = static_cast<QColorDialog *>(editor);
    auto color = color_dialog->currentColor();
    model->setData(index, color, Qt::EditRole);
}

