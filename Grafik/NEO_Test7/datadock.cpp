#include "datadock.h"
#include <QGridLayout>
#include <QtGui>
#include <QDialog>

DataDock::DataDock(QWidget *parent) :
    QDockWidget(parent)
{

    QWidget *wi = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout;

    start = new QLineEdit();
    end = new QLineEdit();

    start->setText("Startnod");
    start->setGeometry(100,80,50,30);


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    layout->addWidget(buttonBox);

    layout->addWidget(start);
    setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    setWindowTitle("Nod-/Bågdata");


    wi->setLayout(layout);
    setWidget(wi);
}

