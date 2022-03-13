#include "ChartUI.h"
#include<QChart>
#include<QValueAxis>
#include<QChartView>
#include<QFormLayout>
#include<QTableView>
#include<QHeaderView>
#include"ChartDelegate.h"
#include"BarChart.h"
#include"PieChart.h"
#include"LineChart.h"
#include<QSplitter>
#include<QToolBar>
#include<QDockWidget>
#include<QPushButton>

chartUI::chartUI(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ProjectC - Editor di grafici");

    setMinimumSize(1024,512);
    QSplitter *splitter = new QSplitter(this);

    buildMenus();

    QToolBar * buts = addToolBar("Opzioni grafico");

    makeButtons();

    for(int i = 0;i<7;i++){
    buts->addWidget(buttons->button(i));
    if(i == 2)
        buts->addSeparator();
    }
    chartDisplay = new QChartView(this);

    chartModel * chart =new chartModel();

    chart->init();

    table = new QTableView(this);

    table->setModel(chart);

    chartContainer = new barChart();

    chartContainer->setModel(chart);

    titleEditor = new QLineEdit(this);
    titleEditor->setPlaceholderText("Titolo del grafico va qui!");

    QDockWidget * titleEditorBar = new QDockWidget(this);

    titleEditorBar->setWidget(titleEditor);
    titleEditorBar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::TopDockWidgetArea,titleEditorBar);

    splitter->addWidget(table);
    splitter->addWidget(chartDisplay);
    setupChart();
    setupSignals();

    setCentralWidget(splitter);
}

void chartUI::setupChart() const{

    table->setItemDelegate(chartContainer->getDelegate());
    chartDisplay->setChart(chartContainer);
    chartContainer->draw();
}

void chartUI::setupSignals() const{
     QHeaderView * vHeader = table->verticalHeader();
     QHeaderView * hHeader = table->horizontalHeader();

     connect(hHeader,SIGNAL(sectionDoubleClicked(int)),chartContainer->getModel(),SLOT(spawnTimelineMod(int)));
     connect(vHeader,SIGNAL(sectionDoubleClicked(int)),chartContainer->getModel(),SLOT(spawnLabelMod(int)));

     connect(this,SIGNAL(pushRow()),chartContainer->getModel(),SLOT(pushRow()));
     connect(this,SIGNAL(pushColumn()),chartContainer->getModel(),SLOT(pushColumn()));
     connect(this,SIGNAL(popColumn()),chartContainer->getModel(),SLOT(popColumn()));
     connect(this,SIGNAL(popRow()),chartContainer->getModel(),SLOT(popRow()));

     connect(titleEditor,SIGNAL(textEdited(QString)),chartContainer->getModel(),SLOT(setTitle(QString)));
     connect(chartContainer->getModel(),SIGNAL(sendText(QString)),titleEditor,SLOT(setText(QString)));
}


chartUI::~chartUI()
{
}

