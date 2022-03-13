#include "BarChart.h"
#include <QTableView>
#include <QBarSet>

barChart::barChart(chartModel * chart) : chartDrawable(chart)
{
  axisX = new QBarCategoryAxis(this);
  axisY = new QValueAxis(this);

  axisX->setLabelsAngle(25);
  legend()->setVisible(true);
  legend()->setAlignment(Qt::AlignBottom);
}

barChart::~barChart(){
    removeAllSeries();
    delete axisX;
    delete axisY;
}
void barChart::updateSeries()
{
    removeAllSeries();
    QBarSeries * barseries = new QBarSeries(this);
    for(int i = 0; i < getModel()->rowCount();i++)
    {
       QBarSet * setP = new QBarSet(getModel()->headerData(i,Qt::Vertical).toString(),barseries);
       for(int j = 0;j < getModel()->columnCount();j++){
               if(getModel()->data(getModel()->index(i,j)).canConvert<double>())
               *setP << getModel()->data(getModel()->index(i,j)).value<double>();
            }
       barseries->append(setP);
        }
    barseries->attachAxis(axisX);
    barseries->attachAxis(axisY);
    addSeries(barseries);
}


void barChart::draw(){

    double max = 0;
    double min = 0;
    if(getModel()->columnCount() != 0 && getModel()->rowCount() != 0){
    for(int i = 0; i < getModel()->rowCount();i++)
    {for(int j = 0;j < getModel()->columnCount();j++){
               if( getModel()->data(getModel()->index(i,j)).canConvert<double>()){
               double aux = getModel()->data(getModel()->index(i,j)).value<double>();
               if(aux > max)
                   max = aux;
               if(aux < min)
                   min = aux;
               }
            }
        }
    }

    QStringList cats;
    for(int i = 0;i< getModel()->columnCount();i++){
        cats << getModel()->headerData(i,Qt::Horizontal).toString();
    }
    axisX->setCategories(cats);
    axisY->setRange(min,max);

    updateTitle();

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);


    updateSeries();
}
