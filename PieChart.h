#ifndef PIECHART_H
#define PIECHART_H
#include"ChartDrawable.h"
#include<QPieSeries>
#include <QChart>
class pieChart : public chartDrawable
{
    Q_OBJECT;
public:
    explicit pieChart(chartModel * chart = nullptr);
    ~pieChart();
    void draw() override;
    void updateSeries() override;
};

#endif // PIECHART_H
