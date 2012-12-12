#ifndef DATADOCK_H
#define DATADOCK_H

#include <QDockWidget>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtGui/QGraphicsView>
#include <string>
#include "graphicnode.h"

class DataDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit DataDock(QWidget *parent = 0);
    void editnodeName(QString);
    void editnodeFlow(QString);
    void editnodePrice(QString);

    double nodeFlow();
    std::string nodeName();
    void change_currentnode(GraphicNode*);
    GraphicNode* return_current_node();

private:
    QLineEdit *nodeName_, *nodeFlow_, *nodePrice_;
    QPushButton *change_node_info_;
    GraphicNode *current_node;
    //Lista med alla noder i interfacet
    //QList<GraphicNode *> nodeList;
    
    
};

#endif // DATADOCK_H
