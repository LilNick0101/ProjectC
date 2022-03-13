
#include <QChart>
#ifndef CHARTDRAWABLE_H
#define CHARTDRAWABLE_H
#include "ChartModel.h"
QT_CHARTS_USE_NAMESPACE

class chartDelegate;
class QTableView;

class chartDrawable : public QChart
{
    Q_OBJECT
private:
    chartModel * chartPointer;
    chartDelegate * delegate;
public:
    explicit chartDrawable(chartModel * chart = nullptr);
    virtual ~chartDrawable();

    virtual void updateSeries() = 0;
    chartModel * getModel() const;
    chartDelegate * getDelegate() const;

    void setModel(chartModel * target);

    void updateTitle();
signals:
     void addColumn(int n);

     void removeColumn(int n);

     void addRow(int n);
public slots:
    virtual void draw() = 0;
};

#endif // CHARTDRAWABLE_H
