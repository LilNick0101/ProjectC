#ifndef BARCHART_H
#define BARCHART_H

#include<QBarSeries>
#include<QValueAxis>
#include <QBarCategoryAxis>
#include "ChartDrawable.h"

class barChart : public chartDrawable
{
    Q_OBJECT
private:
     QBarCategoryAxis* axisX;
     QValueAxis *axisY;

public:
    explicit barChart(chartModel * chart = nullptr);
     ~barChart();
    void draw() override;
    void updateSeries() override;
};

#endif // BARCHART_H
