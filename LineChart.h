#include "ChartDrawable.h"
#include<QLineSeries>
#include <QCategoryAxis>
#include<QValueAxis>
#ifndef LINECHART_H
#define LINECHART_H

class lineChart : public chartDrawable
{
    Q_OBJECT
private:
    QCategoryAxis* axisX;
    QValueAxis * axisY;
public:
    explicit lineChart(chartModel * chart = nullptr);
    ~lineChart();
    void draw() override;
    void updateSeries() override;
    void buildXaxis();
};

#endif // LINECHART_H
