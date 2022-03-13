#include "ChartUI.h"
#include <QPushButton>

void chartUI::makeButtons()
{

    QPushButton * NewFileButton = new QPushButton("Nuovo",this);
    QPushButton * LoadFileButton = new QPushButton("Carica",this);
    QPushButton * SaveFileButton = new QPushButton("Salva",this);
    QPushButton * addRowButton = new QPushButton("Etichetta",this);
    QPushButton * addColumnButton = new QPushButton("Colonna",this);
    QPushButton * removeColumnButton = new QPushButton("Rim. colonna",this);
    QPushButton * removeRowButton = new QPushButton("Rim. etichetta",this);

    NewFileButton->setToolTip("Nuovo file...");
    LoadFileButton->setToolTip("Carica un grafico pre-esistente");
    SaveFileButton->setToolTip("Salva il grafico");
    addRowButton->setToolTip("Aggiungi un etichetta nuova");
    addColumnButton->setToolTip("Aggiungi una colonna vuota");
    removeColumnButton->setToolTip("Rimuove una colonna se ce ne sono");

    buttons = new QButtonGroup();
    buttons->addButton(NewFileButton,0);
    buttons->addButton(LoadFileButton,1);
    buttons->addButton(SaveFileButton,2);
    buttons->addButton(addRowButton,3);
    buttons->addButton(addColumnButton,4);
    buttons->addButton(removeRowButton,5);
    buttons->addButton(removeColumnButton,6);

    connect(buttons->button(0),SIGNAL(clicked()),this,SLOT(NewFile()));

    connect(buttons->button(1),SIGNAL(clicked()),this,SLOT(FileLoader()));

    connect(buttons->button(2),SIGNAL(clicked()),this,SLOT(FileSaver()));

    connect(buttons->button(3),SIGNAL(clicked()),this,SIGNAL(pushRow()));

    connect(buttons->button(4),SIGNAL(clicked()),this,SIGNAL(pushColumn()));

    connect(buttons->button(5),SIGNAL(clicked()),this,SIGNAL(popRow()));

    connect(buttons->button(6),SIGNAL(clicked()),this,SIGNAL(popColumn()));
}
