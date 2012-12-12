//Mari

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cheapest_path_dialog.h"
#include "graphicnode.h"
#include "graphicedge.h"
#include "graphwidget.h"
#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include <typeinfo>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    net(new Network)
{

  setupMenuBar();
  ui->setupUi(this);
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
  file->addSeparator();
  file->addAction(quit);

  QMenu *edit = new QMenu("Edit", qwmb);
  QWidget *qedit = dynamic_cast<QWidget*>(edit);

  QAction *add_node = new QAction("Add node",qedit);
  QAction *remove_node = new QAction("Remove node",qedit);
  QAction *add_edge = new QAction("Add edge",qedit);
  QAction *remove_edge = new QAction("Remove edge",qedit);

  edit->addAction(add_node);
  edit->addAction(remove_node);
  edit->addAction(add_edge);
  edit->addAction(remove_edge);

  QMenu *solve = new QMenu("Solve", qwmb);
  QWidget *qsolve = dynamic_cast<QWidget*>(solve);

  QAction *min_cost_flow = new QAction("Min cost flow",qsolve);
  QAction *max_cost_flow = new QAction("Max cost flow",qsolve);
  QAction *max_flow = new QAction("Max flow",qsolve);
  QAction *cheapest_tree = new QAction("Cheapest tree", qsolve);
  QAction *cheapest_path = new QAction("Cheapest path...",qsolve);

  solve->addAction(min_cost_flow);
  solve->addAction(max_cost_flow);
  solve->addAction(max_flow);
  solve->addAction(cheapest_tree);
  solve->addAction(cheapest_path);

  QMenu *help = new QMenu("Help", qwmb);
  menubar->addMenu(file);
  menubar->addMenu(edit);
  menubar->addMenu(solve);
  menubar->addMenu(help);
  setMenuBar(menubar);

  connect(quit, SIGNAL(triggered()), this, SLOT(close()));
  connect(save_proj, SIGNAL(triggered()), this, SLOT(saveProj()));
  connect(min_cost_flow, SIGNAL(triggered()), this, SLOT(min_cost_flow()));
  connect(max_cost_flow, SIGNAL(triggered()), this, SLOT(max_cost_flow()));
  connect(max_flow,SIGNAL(triggered()), this, SLOT(max_flow()));
  connect(cheapest_tree, SIGNAL(triggered()), this, SLOT(cheapest_tree()));
  connect(cheapest_path, SIGNAL(triggered()), this, SLOT(cheapest_path()));
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

void
MainWindow::min_cost_flow()
{
  try
    {
      net->min_cost_flow();
    }
  catch (network_error &e)
    {
      QString msg = tr("Error calculating minimum cost flow\n%1")
	.arg(e.what());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }

  // Visa någon dialogruta med lösningen.
}

void
MainWindow::max_cost_flow()
{
  try
    {
      net->max_cost_flow();
    }
  catch (network_error &e)
    {
      QString msg = tr("Error calculating maximum cost flow\n%1")
	.arg(e.what());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }

  // Visa någon dialogruta med lösningen.
}

void
MainWindow::max_flow()
{
  try
    {
      net->max_flow();
    }
  catch (network_error &e)
    {
      QString msg = tr("Error calculating maximum flow\n%1")
	.arg(e.what());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }

  // Visa någon dialogruta med lösningen.
}

void
MainWindow::cheapest_tree()
{
  try
    {
      net->cheapest_tree();
    }
  catch (network_error &e)
    {
      QString msg = tr("Error calculating cheapest tree\n%1")
	.arg(e.what());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }

  // Visa någon dialogruta med lösningen.
}

void
MainWindow::cheapest_path()
{
  CheapestPathDialog *dialog = new CheapestPathDialog(this);
  dialog->exec();
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
