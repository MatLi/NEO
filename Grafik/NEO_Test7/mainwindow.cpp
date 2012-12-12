//Mari

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datadock.h"
#include "addedgedock.h"
#include <QDockWidget>
#include <QDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("NEO - Elegant Optimization");

    dock = new DataDock(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock2 = new AddEdgeDock(this);
    addDockWidget(Qt::LeftDockWidgetArea,dock2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

AddEdgeDock* MainWindow::return_AddEdgeDock()
{
    return dock2;
}

DataDock* MainWindow::return_DataDock()
{
    return dock;
}
