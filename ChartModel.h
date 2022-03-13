#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "ChartGlobal.h"
class chartModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    chartGlobal * chart;
public:
    chartModel(chartGlobal * ch, QObject * parent = nullptr);

    chartModel(QObject * parent = nullptr);

    chartModel(const chartModel & copy);

    chartModel & operator=(const chartModel & assing);

    ~chartModel();

    double obtainTotal(u_int32 row) const;

    QString getTitle() const;

    int	columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void init();

    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void draw();

    void sendText(const QString & text);
public slots:
    void setTitle(const QString & text);

    void pushColumn();

    void spawnLabelMod(int index);

    void spawnTimelineMod(int index);

    void popColumn();

    void pushRow();

    void popRow();

    void reset();
};

#endif // CHARTMODEL_H
