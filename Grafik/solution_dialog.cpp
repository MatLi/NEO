/*
 * FILENAME:      solution_dialog.cpp
 * PROJECT:       NEO
 * PROGRAMMER:    David
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * SolutionDialog displayes the soutions to the user.
 */

#include <QtGui>
#include <string>
#include "solution_dialog.h"
#include "graphicnode.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "Network.h"
#include "Edge.h"
#include "Set.h"
#include "Node.h"
using namespace std;

SolutionDialog::SolutionDialog(Solution sol, QWidget *parent) :
  QDialog(parent)
{
  QString textSolution = "Default..."; 
  switch (sol)
    {
    case min_cf:
      setWindowTitle("Minimum cost flow solution");
      minCostFlow(textSolution);
      break;
    case max_cf:
      setWindowTitle("Maximum cost flow solution");
      maxCostFlow(textSolution);
      break;
    case max_f:
      setWindowTitle("Maximum flow solution");
      maxFlow(textSolution);
      break;
    case c_tree:
      setWindowTitle("Cheapest tree solution");
      cheapestTree(textSolution);
      break;
    case c_path:
      setWindowTitle("Cheapest path solution");
      cheapestPath(textSolution);
      break;
    default:
      setWindowTitle("This never happens...");
      textSolution = "This never happens...";
      break;
}

QPlainTextEdit* plainText = new QPlainTextEdit(textSolution, this);
plainText->setReadOnly(true);
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Close);
  QGridLayout *ctDialogLayout = new QGridLayout(dynamic_cast<QWidget*>(this));

ctDialogLayout->addWidget(dynamic_cast<QWidget*>(plainText),0,0);
ctDialogLayout->addWidget(dynamic_cast<QWidget*>(buttonBox),1,0);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  
  setLayout(ctDialogLayout);
}

void
SolutionDialog::save()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save solution in text format"));

  if (fileName.isEmpty())
    {
      return;
    }

  QFile file(fileName);

  if (!file.open(QFile::WriteOnly))
    {
      QString msg = tr("Failed to open %1\n%2")
	.arg(fileName)
	.arg(file.errorString());
	     QMessageBox::warning(this, tr("Error"), msg);
	     return;
    }

  QByteArray text;
  text.insert(0, textSolution);
  bool ok = file.write(text);

  if (!ok)
    {
      QString msg = tr("Error writing to %1\n%2")
	.arg(fileName)
	.arg(file.errorString());
      QMessageBox::warning(this, tr("Error"), msg);
      return;
    }
  return;
}

void SolutionDialog::minCostFlow(QString& text)
{
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  QString qsFlowCost;
  qsFlowCost.setNum(mw->net->flowcost());
  text.append(tr("Minimum cost flow solution\n"));
  text.append(tr("==========================\n\n"));
  text.append(tr("Flow cost: "));
  text.append(qsFlowCost);
  text.append("\n\n");
  text.append(tr("Nodes with their flow\n"));
  for (auto it : mw->net->node_set())
    {
      QString qsFlow;
      string sNode = "Node " + (*it).name() + ": ";
      QString qsNode(sNode.c_str());
      qsFlow.setNum((*it).flow());
      text.append(qsNode);
      text.append(qsFlow);
      text.append("\n");
    }
	text.append(tr("\n\n\n"));
  text.append(tr("Edges with flow > 0\n"));
  for (auto it : mw->net->edge_set())
    {
      if ((*it).flow() > 0)
	{
	  QString qsFlow;
	  string sEdge = (*it).from_node()->name() + "->" + (*it).to_node()->name() + ": ";
	  QString qsEdge(sEdge.c_str());
	  qsFlow.setNum((*it).flow());
	  text.append(qsEdge);
	  text.append(qsFlow);
	  text.append("\n");
	}
    }
  return;
}

void SolutionDialog::maxCostFlow(QString& text)
{
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  QString qsFlowCost;
  qsFlowCost.setNum(mw->net->flowcost());
  text.append(tr("Maximum cost flow solution\n"));
  text.append(tr("==========================\n\n"));
  text.append(tr("Flow cost: "));
  text.append(qsFlowCost);
  text.append("\n\n");
  text.append(tr("Nodes with their flow\n"));
  for (auto it : mw->net->node_set())
    {
      QString qsFlow;
      string sNode = "Node " + (*it).name() + ": ";
      QString qsNode(sNode.c_str());
      qsFlow.setNum((*it).flow());
      text.append(qsNode);
      text.append(qsFlow);
      text.append("\n");
    }
	text.append(tr("\n\n\n"));
  text.append(tr("Edges with flow > 0\n"));
  for (auto it : mw->net->edge_set())
    {
      if ((*it).flow() > 0)
	{
	  QString qsFlow;
	  string sEdge = (*it).from_node()->name() + "->" + (*it).to_node()->name() + ": ";
	  QString qsEdge(sEdge.c_str());
	  qsFlow.setNum((*it).flow());
	  text.append(qsEdge);
	  text.append(qsFlow);
	  text.append("\n");
	}
    }
  return;
}

void SolutionDialog::maxFlow(QString& text)
{
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  text.append(tr("Maximum flow solution\n"));
  text.append(tr("=====================\n\n"));
  text.append(tr("Nodes with their flow\n"));
  for (auto it : mw->net->node_set())
    {
      QString qsFlow;
      string sNode = "Node " + (*it).name() + ": ";
      QString qsNode(sNode.c_str());
      qsFlow.setNum((*it).flow());
      text.append(qsNode);
      text.append(qsFlow);
      text.append("\n");
    }
	text.append(tr("\n\n\n"));
  text.append(tr("Edges with flow > 0\n"));
  for (auto it : mw->net->edge_set())
    {
      if ((*it).flow() > 0)
	{
	  QString qsFlow;
	  string sEdge = (*it).from_node()->name() + "->" + (*it).to_node()->name() + ": ";
	  QString qsEdge(sEdge.c_str());
	  qsFlow.setNum((*it).flow());
	  text.append(qsEdge);
	  text.append(qsFlow);
	  text.append("\n");
	}
    }
  return;
}

void SolutionDialog::cheapestTree(QString& text)
{
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  text.append(tr("Cheapest tree solution\n"));
  text.append(tr("==========================\n\n"));
  text.append(tr("Edges in tree\n"));
  for (auto it : mw->net->edge_set())
    {
      if ((*it).flow() > 0)
	{
	  string sEdge = (*it).from_node()->name() + "->" + (*it).to_node()->name();
	  QString qsEdge(sEdge.c_str());
	  text.append(qsEdge);
	}
    }
  return;
}

void SolutionDialog::cheapestPath(QString& text)
{
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());
  text.append(tr("Cheapest path solution\n"));
  text.append(tr("======================\n\n"));

  text.append(tr("Edges in path\n"));
  for (auto it : mw->net->edge_set())
    {
      if ((*it).flow() > 0)
	{
	  string sEdge = (*it).from_node()->name() + "->" + (*it).to_node()->name();
	  QString qsEdge(sEdge.c_str());
	  text.append(qsEdge);
	  text.append("\n");
	}
    }
  return;
}
