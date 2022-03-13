#include "LineChart.h"
#include<QPoint>
#include<QTableView>

lineChart::lineChart(chartModel * chart) : chartDrawable(chart)
{
  axisX = new QCategoryAxis(this);
  axisY = new QValueAxis(this);

  axisX->setLabelsAngle(25);
  axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
  legend()->setVisible(true);
  legend()->setAlignment(Qt::AlignBottom);
}

void lineChart::buildXaxis(){
    delete axisX;
    axisX = new QCategoryAxis(this);
    QStringList cats;
    int i = 0;
    while(i< getModel()->columnCount()){
        axisX->append(getModel()->headerData(i,Qt::Horizontal).toString(),1*i);
            i++;
    }
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisX->setLabelsAngle(25);
    axisX->setRange(0,i -1);
    axisX->setStartValue(0);
}

lineChart::~lineChart(){
    removeAllSeries();
    delete axisX;
    delete axisY;
}
void lineChart::updateSeries()
{
    removeAllSeries();
    for(int i = 0; i < getModel()->rowCount();i++)
    {
       QLineSeries * canvasSeries = new QLineSeries(this);

       canvasSeries->setName(getModel()->headerData(i,Qt::Vertical).toString());
       for(int j = 0;j < getModel()->columnCount();j++){
           *canvasSeries << QPoint(j,getModel()->data(getModel()->index(i,j)).toDouble());
       }
       addSeries(canvasSeries);
       canvasSeries->attachAxis(axisY);
       canvasSeries->attachAxis(axisX);
     }
}


void lineChart::draw(){
    double max = 0;
    double min = 0;
    if(getModel()->columnCount() != 0 && getModel()->rowCount() != 0){
    for(int i = 0; i < getModel()->rowCount();i++)
    {for(int j = 0;j < getModel()->columnCount();j++){
               double aux = getModel()->data(getModel()->index(i,j)).value<double>();
               if(aux > max)
                   max = aux;
               if(aux< min)
                   min = aux;
            }
        }
    }

    buildXaxis();

    axisY->setRange(min,max);

    updateTitle();
    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);


    updateSeries();
}
