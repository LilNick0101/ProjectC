#include "ChartDelegate.h"
#include <QTableView>
#include <QLineEdit>
#include "ChartModel.h"

chartDelegate::chartDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget * chartDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const {
    QLineEdit *valueEditor = new QLineEdit(parent);
    return valueEditor;
}

void chartDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if(index.isValid()){
        const chartModel * chartMod = dynamic_cast<const chartModel*>(index.model());
        QVariant value = chartMod->data(index);
        QLineEdit * valueEditor = dynamic_cast<QLineEdit*>(editor);
        valueEditor->insert(value.toString());
    }
}

void chartDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    if(index.isValid()){
        QLineEdit* valueEditor = dynamic_cast<QLineEdit*>(editor);
        QVariant value = valueEditor->text();
        chartModel * chartMod = dynamic_cast<chartModel*>(model);
        chartMod->setData(index,value);
    }
}
