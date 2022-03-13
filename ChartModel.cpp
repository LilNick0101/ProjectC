#include "ChartModel.h"
#include <QInputDialog>
chartModel::chartModel(QObject * parent) : QAbstractTableModel(parent), chart(new chartGlobal()){

}

chartModel::chartModel(chartGlobal * ch,QObject * parent) : QAbstractTableModel(parent), chart(ch){

}

chartModel::chartModel(const chartModel & copy) : chart(new chartGlobal(*copy.chart)){}

chartModel & chartModel::operator=(const chartModel &assign){
    if(this != &assign){
        delete chart;
        chart = new chartGlobal(*assign.chart);
    }
    return *this;
}

chartModel::~chartModel(){
    delete chart;
    disconnect(this,0,0,0);
}

QString chartModel::getTitle() const{
    return chart->getTitle().c_str();
}

void chartModel::setTitle(const QString &text){
    chart->setTitle(text.toStdString());
    emit sendText(chart->getTitle().c_str());
    emit draw();
}

int chartModel::columnCount(const QModelIndex & parent) const{
    Q_UNUSED(parent);
    return chart->tableWidth();
};

int chartModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return chart->tableHeight();
}

QVariant chartModel::data(const QModelIndex &index, int role) const{
    try{
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        return chart->atIndex(index.row(),index.column());
           }
    return QVariant();
    }
    catch(std::string x){

        return QVariant();
    }
}

QVariant chartModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role == Qt::DisplayRole || role == Qt::EditRole){
    if(orientation == Qt::Vertical)
        return  chart->getLabel(section).c_str();
    else if(orientation == Qt::Horizontal)
        return chart->atTimelineIndex(section).c_str();
    }

    return QVariant();
}

bool chartModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role){
    try{
      if (section < rowCount() && role == Qt::EditRole && orientation == Qt::Vertical){
        chart->setLabel(section,value.toString().toStdString());
      }
      else if(section < columnCount() && role == Qt::EditRole && orientation == Qt::Horizontal){
         chart->modTimelineIndex(section,value.toString().toStdString());
            }
      emit headerDataChanged(orientation,section,section);
      emit draw();
      return true;
    }
    catch(std::string x){
        return false;
    }
}
bool chartModel::setData(const QModelIndex &index, const QVariant &value, int role){
    try{
      if (index.isValid() && role == Qt::EditRole){
        chart->modIndex(index.row(),index.column(),value.toDouble());
      emit draw();
      return true;
      }
      return false;
    }
    catch(std::string x){
        return false;
    }
}

bool chartModel::insertColumns(int column, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    column = columnCount();
    try{
    if(count < 0 && columnCount() <= 0) throw std::string("Negative count");
    beginInsertColumns(QModelIndex(),column,column+ count - 1);
    chart->addColumn(0,count);

    endInsertColumns();

    return true;
    }
    catch(std::string x){
        return false;
    }
}

double chartModel::obtainTotal(u_int32 row) const{
    if(row < rowCount())
        return chart->operator[](row)->obtainTotal();
    else
        return 0;
}

bool chartModel::removeColumns(int column, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    column = columnCount() - 1;
    try{
    if(column <= 0) return false;

    beginRemoveColumns(QModelIndex(),column - (count-1),column);

    chart->removeColumn(count);

    endRemoveColumns();

    return true;

    }catch(std::string x){

        return false;
    }
}

bool chartModel::insertRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    row = rowCount();
    try{
    if(count < 0) return false;
        beginInsertRows(QModelIndex(),row,row+count-1);
        for(int j = 0;j < count;j++){
            chart->addEntry((QString("Label %1").arg(row + j)).toStdString(),row + j);
        }
        endInsertRows();

        return true;
    }catch (std::string x) {
        return false;
     }
}

bool chartModel::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);
    row = rowCount() - 1;
    if(row <= 0) return false;
    try{

    beginRemoveRows(QModelIndex(),row - (count-1),row);
    chart->removeEntry(count);

    endRemoveRows();
    return true;

    }catch(std::string x){
        return false;
    }
}

void chartModel::pushColumn(){
    if(insertColumns(0,1))
    emit draw();
}

void chartModel::popColumn(){
    if(removeColumns(0,1))
    emit draw();
}

void chartModel::pushRow(){
    if(insertRows(0,1))
    emit draw();
}

void chartModel::spawnLabelMod(int index){
    bool ok;
    QString text = QInputDialog::getText(nullptr,"Modifica etichetta",QString("Modifica l'etichetta %1").arg(headerData(index,Qt::Vertical).toString()),QLineEdit::Normal,headerData(index,Qt::Vertical).toString(),&ok);
    if(ok)
    chart->setLabel(index,text.toStdString());
    emit draw();
}

void chartModel::spawnTimelineMod(int index){
    bool ok;
    QString text = QInputDialog::getText(nullptr,"Modifica etichetta",QString("Modifica l'istanza %1").arg(headerData(index,Qt::Horizontal).toString()),QLineEdit::Normal,headerData(index,Qt::Horizontal).toString(),&ok);
    if(ok)
    chart->modTimelineIndex(index,text.toStdString());
    emit draw();
}

void chartModel::popRow(){
    if(removeRows(0,1))
    emit draw();

}
Qt::ItemFlags chartModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


void chartModel::init(){
    if(rowCount() == 0 && columnCount() == 0){
        insertRows(0,1);
        insertColumns(0,1);
    }
}
void chartModel::reset(){
    beginResetModel();
    delete chart;
    chart = new chartGlobal();
    endResetModel();
    init();
}
