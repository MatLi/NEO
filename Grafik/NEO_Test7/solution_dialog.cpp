#include <QtGui>
#include "solution_dialog.h"
#include "graphicnode.h"
#include "graphwidget.h"
#include "mainwindow.h"

SolutionDialog::SolutionDialog(Solution sol, QWidget *parent) :
  QDialog(parent)
{
  QString textSolution = "Default..."; 
  switch (sol)
    {
    case min_cf:
      setWindowTitle("Minimum cost flow solution");
      min_cost_flow(textSolution);
      break;
    case max_cf:
      setWindowTitle("Maximum cost flow solution");
      max_cost_flow(textSolution);
      break;
    case max_f:
      setWindowTitle("Maximum flow solution");
      max_flow(textSolution);
      break;
    case c_tree:
      setWindowTitle("Cheapest tree solution");
      cheapest_tree(textSolution);
      break;
    case c_path:
      setWindowTitle("Cheapest path solution");
      cheapest_path(textSolution);
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

void
SolutionDialog::min_cost_flow(QString& text)
{
  
  return;
}

void
SolutionDialog::max_cost_flow(QString& text)
{
  return;
}

void
SolutionDialog::max_flow(QString& text)
{
  return;
}

void
SolutionDialog::cheapest_tree(QString& text)
{
  return;
}

void
SolutionDialog::cheapest_path(QString& text)
{
  return;
}
