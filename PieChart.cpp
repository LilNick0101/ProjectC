#include "PieChart.h"
#include<QTableView>
pieChart::pieChart(chartModel * chart) : chartDrawable(chart)
{
}

pieChart::~pieChart(){
    removeAllSeries();
}
void pieChart::draw(){
    updateTitle();

    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignBottom);

    updateSeries();
}

void pieChart::updateSeries()
{
    removeAllSeries();
    QPieSeries * canvasSeries = new QPieSeries(this);
    for(int it = 0; it < getModel()->rowCount();it++)
          {
             QPieSlice * setP = new QPieSlice(getModel()->headerData(it,Qt::Vertical).toString(),getModel()->obtainTotal(it),canvasSeries);
             setP->setLabelVisible();
             canvasSeries->append(setP);
     }

    addSeries(canvasSeries);
}
