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
  CheapestPathDialog(QString &start_node, QString &end_node, QWidget *parent = 0);
  ~CheapestPathDialog() = default;

public slots:

private slots:

private:
};

#endif // MAINWINDOW_H
