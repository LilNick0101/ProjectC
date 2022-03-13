#include"BarChart.h"
#include"PieChart.h"
#include"LineChart.h"
#include "ChartUI.h"
#include<QFileDialog>
#include"ChartModel.h"
#include<QVariant>
#include<QErrorMessage>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QTableView>
#include<QStandardPaths>
#include<QStatusBar>
#include<QMessageBox>
#include<QHeaderView>

void chartUI::FileLoader(){
    QString filter = tr("File JSON (*.json)");
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Scegli un file dati"), QStandardPaths::writableLocation(QStandardPaths::HomeLocation), filter,&filter);

    chartModel * newChart;
    newChart = new chartModel();
try{
    if(!fileName.isEmpty()){
        QFile file(fileName);

        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QString val = file.readAll();

            QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
            if(d.object().contains("title") && d.object().value("title").isString())
                newChart->setTitle(d.object().value("title").toString());
            else
                newChart->setTitle("Default title");

            if(d.object().contains("labels") && d.object().value("labels").isArray()){
                QJsonArray content = d.object().value("labels").toArray();


                for(int i = 0;i < content.size(); i++){
                    QJsonObject aux = content[i].toObject();
                    if(!aux.isEmpty() && aux.contains("name") && aux.contains("values") && aux.value("values").isArray()){
                        QString lab = aux.value("name").toString();
                        newChart->pushRow();
                        newChart->setHeaderData(i,Qt::Vertical,lab);
                        QJsonArray vals = aux.value("values").toArray();
                        for(int j = 0;j< vals.size();j++){
                            if(j >= newChart->columnCount())
                                newChart->pushColumn();
                            newChart->setData(newChart->index(i,j),vals[j].toDouble());
                        }
                    }else throw QErrorMessage::qtHandler();
                }
               if(d.object().contains("timeline") && d.object().value("timeline").isArray()){
                       QJsonArray content = d.object().value("timeline").toArray();
                       for(int j = 0;j< content.size();j++){
                           if(j >= newChart->columnCount())
                               newChart->pushColumn();
                           newChart->setHeaderData(j,Qt::Horizontal,content[j].toString());
                       }
                }

            } else throw QErrorMessage::qtHandler();
            chartModel * toDelete = chartContainer->getModel();
            chartContainer->setModel(newChart);
            table->setModel(newChart);
            delete toDelete;
            setupChart();
            setupSignals();
            statusBar()->showMessage(QString("Caricato con successo %1").arg(fileName),10000);
            }
       }
    }
    catch(QErrorMessage * e){
        delete newChart;
        e->showMessage("Formato file errato!");
    }
}

void chartUI::FileSaver(){

    QString filter = tr("File JSON (*.json)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva il file") , QStandardPaths::writableLocation(QStandardPaths::HomeLocation),filter,&filter);

    if(!fileName.isEmpty()){

    QJsonArray labels = QJsonArray();
    chartModel * aus = chartContainer->getModel();
    for(int i = 0;i<aus->rowCount();i++){
        QJsonObject aux = QJsonObject();
        aux.insert("name",aus->headerData(i,Qt::Vertical).toString());
        QJsonArray vals = QJsonArray();
        for(int j = 0;j<aus->columnCount();j++){
            vals << aus->data(aus->index(i,j)).toDouble();
        }
        aux.insert("values",vals);
        labels << aux;
    }
    QJsonArray tmln = QJsonArray();
    for(int j = 0;j<aus->columnCount();j++){
        tmln << aus->headerData(j,Qt::Horizontal).toString();
    }
    QJsonObject labelList = QJsonObject();

    labelList.insert("title",aus->getTitle());

    labelList.insert("labels",labels);

    labelList.insert("timeline",tmln);
    QByteArray final = QJsonDocument(labelList).toJson();
    QFile output(fileName);
    if(output.open(QIODevice::WriteOnly | QIODevice::Text)){
        output.write(final);
            }
    statusBar()->showMessage(QString("Salvato con successo %1").arg(fileName),10000);
    }
}

void chartUI::NewFile(){
    chartContainer->getModel()->reset();
    chartContainer->draw();
}
