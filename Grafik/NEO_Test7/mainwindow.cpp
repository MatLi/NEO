//Mari

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include "datadock.h"
#include "addedgedock.h"
#include <QDockWidget>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    net(new Network)
{
  setupMenuBar();
  ui->setupUi(this);
  
  setWindowTitle("NEO - Elegant Optimization");

  dock = new DataDock(this);
  addDockWidget(Qt::RightDockWidgetArea, dock);

  dock2 = new AddEdgeDock(this);
  addDockWidget(Qt::LeftDockWidgetArea,dock2);
}

void
MainWindow::setupMenuBar()
{
  QMenuBar *menubar = new QMenuBar(dynamic_cast<QWidget*>(this));
  QWidget *qwmb = dynamic_cast<QWidget*>(menubar);
  QMenu *file = new QMenu("File", qwmb);
  QWidget *qwf = dynamic_cast<QWidget*>(file);
  QAction *new_proj = new QAction("New model", qwf);
  QAction *open_proj = new QAction("Open model...", qwf);
  QAction *save_proj = new QAction("Save model", qwf);
  QAction *export_graph = new QAction("Export graph to .svg", qwf);
  QAction *quit = new QAction("Quit", qwf);

  file->addAction(new_proj);
  file->addAction(open_proj);
  file->addAction(save_proj);
  file->addAction(export_graph);
  file->addAction(quit);

  connect(quit, SIGNAL(triggered()), this, SLOT(close()));
  connect(save_proj, SIGNAL(triggered()), this, SLOT(saveProj()));

  QMenu *edit = new QMenu(qwmb);
  edit->setTitle("Edit");
  QMenu *solve = new QMenu(qwmb);
  solve->setTitle("Solve");
  QMenu *help = new QMenu(qwmb);
  help->setTitle("Help");
  menubar->addMenu(file);
  menubar->addMenu(edit);
  menubar->addMenu(solve);
  menubar->addMenu(help);
  setMenuBar(menubar);
  return;
}


MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::saveProj()
{
  QString fileName
    = QFileDialog::getSaveFileName(this, tr("Save model"));
  if (fileName.isEmpty())
    return;

  try
    {
      net->fwrite(fileName.toStdString());
    }
  catch (network_error &e)
    {
      QMessageBox::warning(this, tr("Error"), e.what());
    }
  return;
}

AddEdgeDock* MainWindow::return_AddEdgeDock()
{
    return dock2;
}

DataDock* MainWindow::return_DataDock()
{
    return dock;
}
