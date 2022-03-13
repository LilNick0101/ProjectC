#include "ChartUI.h"
#include "BarChart.h"
#include "LineChart.h"
#include "PieChart.h"
#include <QTableView>
void chartUI::buildMenus()
{
    QMenuBar * menuBar = new QMenuBar(this); //creazione barra menu

    QMenu * fileManager = new QMenu("File",menuBar);

    menuBar->addMenu(fileManager);
    fileManager->addAction("Nuovo",this,SLOT(NewFile()),Qt::Key_F1);
    fileManager->addAction("Carica",this,SLOT(FileLoader()),Qt::Key_F2);
    fileManager->addAction("Salva",this,SLOT(FileSaver()),Qt::Key_F3);
    fileManager->addSeparator();
    fileManager->addAction("Esci",qApp,SLOT(quit()),Qt::Key_Escape);

    QMenu * chartMenu = new QMenu("Grafico",menuBar);
    QMenu * changeView = new QMenu("Cambia vista",chartMenu);
    QMenu * addStuffMenu = new QMenu("Aggiungi",chartMenu);

    addStuffMenu->addAction("Etichetta vuota",this,SIGNAL(pushRow()),QKeySequence::AddTab);
    addStuffMenu->addAction("Colonna vuota",this,SIGNAL(pushColumn()));

    pieChange = new QAction("Grafico a torta",changeView);
    pieChange->setCheckable(true);
    changeView->addAction(pieChange);
    lineChange =new QAction("Grafico cartesiano",changeView);

    lineChange->setCheckable(true);
    changeView->addAction(lineChange);

    barChange = new QAction("Grafico a barre",changeView);

    barChange->setCheckable(true);
    changeView->addAction(barChange);

    chartMenu->addMenu(addStuffMenu);

    chartMenu->addMenu(changeView);

    menuBar->addMenu(chartMenu);

    QMenu * other = new QMenu("Altro",menuBar);

    other->addAction("About...",this,SLOT(showAboutDialog()));
    connect(barChange,SIGNAL(toggled(bool)),this,SLOT(changeToBar(bool)));
    connect(lineChange,SIGNAL(toggled(bool)),this,SLOT(changeToLine(bool)));
    connect(pieChange,SIGNAL(toggled(bool)),this,SLOT(changeToPie(bool)));
    menuBar->addMenu(other);

    setMenuBar(menuBar);

}

void chartUI::showAboutDialog(){
    QMessageBox::about(this, "About...","ProjectC by Nicola Ravagnan AA 2021/2022");
}

void chartUI::changeToBar(bool i){
    if(i){
        lineChange->setChecked(false);
        pieChange->setChecked(false);

        chartModel * aux = chartContainer->getModel();
        chartDrawable * toDelete = chartContainer;
        chartContainer = new barChart(aux);
        setupChart();
        delete toDelete;

    }
}

void chartUI::changeToLine(bool i){
    if(i){
        barChange->setChecked(false);
        pieChange->setChecked(false);

        chartModel * aux = chartContainer->getModel();
        chartDrawable * toDelete = chartContainer;
        chartContainer = new lineChart(aux);
        setupChart();
        delete toDelete;
    }
}

void chartUI::changeToPie(bool i){
    if(i){
        lineChange->setChecked(false);
        barChange->setChecked(false);

        chartModel * aux = chartContainer->getModel();
         chartDrawable * toDelete = chartContainer;
        chartContainer = new pieChart(aux);
        setupChart();
        delete toDelete;
        }
}
