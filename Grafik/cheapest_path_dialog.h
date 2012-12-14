/* 
 * FILENAME:      cheapest_path_dialog.h
 * PROJEKT:       NEO
 * PROGRAMMER:    David
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Dialog window that appears when solving cheapest path problems.
 */

#ifndef C_P_DIALOG_H
#define C_P_DIALOG_H

#include <QtGui>
#include "Network.h"
#include "Node.h"
#include "Edge.h"

class CheapestPathDialog : public QDialog
{
    Q_OBJECT
    
public:
  CheapestPathDialog(QWidget *parent = 0);
  ~CheapestPathDialog() = default;

public slots:

private slots:
  void run();
private:
  QLabel *labelStartNode;
  QLabel *labelEndNode;
  QLineEdit *leStartNode;
  QLineEdit *leEndNode;
  QDialogButtonBox *buttonBox;
  QGridLayout *ctDialogLayout;
  QErrorMessage *errorMessageDialog;
  QString start;
  QString end;
};

#endif // MAINWINDOW_H
