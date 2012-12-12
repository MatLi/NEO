//Mari

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Network.h"
#include "Node.h"
#include "Edge.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    net(new Network)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawEllipse(100, 100, 10, 10);

}*/

/*void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Hej hopp");

}*/

/*void MainWindow::on_actionOpen_activated()
{
    ui->setupUi(this);
}*/
