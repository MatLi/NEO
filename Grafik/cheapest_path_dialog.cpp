/* 
 * FILENAME:      cheapest_path_dialog.cpp
 * PROJEKT:       NEO
 * PROGRAMMER:    David
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Dialog window that appears when solving cheapest path problems.
 */

#include <QtGui>
#include "cheapest_path_dialog.h"
#include "solution_dialog.h"
#include "graphicnode.h"
#include "graphwidget.h"
#include "mainwindow.h"

CheapestPathDialog::CheapestPathDialog(QWidget *parent) :
  QDialog(parent)
{
  QLabel *labelStartNode = new QLabel(tr("Start node: "));
  QLabel *labelEndNode = new QLabel(tr("End node: "));
  QLineEdit *leStartNode = new QLineEdit(start);
  QLineEdit *leEndNode = new QLineEdit(end);
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  QGridLayout *ctDialogLayout = new QGridLayout(dynamic_cast<QWidget*>(this));

  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(labelStartNode), 0, 0);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(labelEndNode), 1, 0);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(leStartNode), 0, 1);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(leEndNode), 1, 1);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(buttonBox), 2, 1);
  ctDialogLayout->setColumnStretch(1, 1);
  ctDialogLayout->setColumnMinimumWidth(1, 250);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(run()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  
  setWindowTitle("Give start and end node");
  setLayout(ctDialogLayout);
}

void
CheapestPathDialog::run()
{
  Solution sol_dialog = c_path;
  GraphicNode *startn = nullptr;
  GraphicNode *endn = nullptr;
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  GraphWidget* graph = dynamic_cast<GraphWidget*>(mw->centralWidget());
  QList<GraphicNode*> nodeList = graph->returnNodeList();
  for (int i=0; i < nodeList.size(); i++)
    {
      if(nodeList.at(i)->returnName()==start)
        {
	  startn = nodeList.at(i);
        }
    }

  for (int j=0; j < nodeList.size(); j++)
    {
      if(nodeList.at(j)->returnName()==end)
        {
	  endn=nodeList.at(j);
        }
    }
  try
    {
      if (startn && endn)
	{
	  mw->net->cheapest_path(startn->net_node,endn->net_node);
	}
      else
	{
	  QString msg = tr("Error calculating cheapest tree\nThe nodes you gave do not exist.");
	  QMessageBox::warning(this, tr("Error"), msg);
	  return;
	}
    }
  catch (network_error &e)
    {
      QString msg = tr("Error calculating cheapest tree\n%1")
	.arg(e.what());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }

  SolutionDialog sd(sol_dialog, this);
  sd.show();

}
