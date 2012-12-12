#include <QtGui>
#include "cheapest_path_dialog.h"

CheapestPathDialog::CheapestPathDialog(QString &start_node, QString &end_node, QWidget *parent) :
  QDialog(parent)
{
  QLabel *labelStartNode = new QLabel(tr("Start node: "));
  QLabel *labelEndNode = new QLabel(tr("End node: "));
  QLineEdit *leStartNode = new QLineEdit(start_node);
  QLineEdit *leEndNode = new QLineEdit(end_node);
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  QGridLayout *ctDialogLayout = new QGridLayout(dynamic_cast<QWidget*>(this));

  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(labelStartNode), 0, 0);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(labelEndNode), 1, 0);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(leStartNode), 0, 1);
  ctDialogLayout->addWidget(dynamic_cast<QWidget*>(leEndNode), 1, 1);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  setLayout(ctDialogLayout);
}
