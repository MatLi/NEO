#ifndef SOL_DIALOG_H
#define SOL_DIALOG_H

#include <QtGui>
#include "Network.h"
#include "Node.h"
#include "Edge.h"


enum Solution
  { min_cf, max_cf, max_f, c_tree, c_path  };

class SolutionDialog : public QDialog
{
    Q_OBJECT
    
public:
  SolutionDialog(Solution sol, QWidget *parent = 0);
  ~SolutionDialog() = default;

public slots:

private slots:
  void save();
private:
  QString textSolution;
  QPlainTextEdit* plainText;
  void min_cost_flow(QString&);
  void max_cost_flow(QString&);
  void max_flow(QString&);
  void cheapest_tree(QString&);
  void cheapest_path(QString&);
};

#endif // MAINWINDOW_H
