#ifndef CHARTDELEGATE_H
#define CHARTDELEGATE_H

#include<QStyledItemDelegate>
#include "ChartModel.h"

class QTableView;

class chartDelegate : public QStyledItemDelegate
{
public:
    explicit chartDelegate(QObject *parent = nullptr);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // CHARTDELEGATE_H
