#include "ChartDrawable.h"
#include "ChartModel.h"

#include "ChartDelegate.h"
chartDrawable::chartDrawable(chartModel * chart): chartPointer(chart), delegate(new chartDelegate(this)){
    connect(chartPointer,SIGNAL(draw()),this,SLOT(draw()));
}

chartDrawable::~chartDrawable(){
    disconnect(chartPointer,SIGNAL(draw()),this,SLOT(draw()));
}

chartModel * chartDrawable::getModel() const{return chartPointer;}

chartDelegate * chartDrawable::getDelegate() const{return delegate;}

void chartDrawable::setModel(chartModel * target){
    getModel()->disconnect();
    chartPointer = target;
    connect(chartPointer,SIGNAL(draw()),this,SLOT(draw()));
    draw();
}

void chartDrawable::updateTitle()
{
    setTitle(chartPointer->getTitle());
}


