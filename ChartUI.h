#ifndef CHARTUI_H
#define CHARTUI_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QAction>
#include <QVBoxLayout>//layout verticale
#include <QHBoxLayout>//layout orrizontale
#include <QLineEdit>
#include <QButtonGroup>
#include <QChartView>
#include <QApplication>
#include "ChartDelegate.h"
#include "ChartDrawable.h"
#include <QMessageBox>
class QTableView;

class chartModel;

class chartUI : public QMainWindow
{
private:
    Q_OBJECT

    QChartView * chartDisplay;
    QAction * pieChange;
    QAction * lineChange;
    QAction * barChange;
    QTableView * table;
    QLineEdit * titleEditor;
    chartDrawable * chartContainer;
    QButtonGroup * buttons;
public:
    chartUI(QWidget *parent = nullptr);

    ~chartUI();

    void buildMenus();

    void setupChart() const;

    void setupSignals() const;

    void makeButtons();
    
signals:
    void pushRow();

    void pushColumn();

    void popColumn();

    void popRow();
public slots:
    void FileLoader();

    void FileSaver();

    void NewFile();

    void showAboutDialog();

    void changeToBar(bool i);

    void changeToLine(bool i);

    void changeToPie(bool i);
};
#endif // CHARTUI_H
