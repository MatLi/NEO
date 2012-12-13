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

    void editedgeCost(QString);
    void editedgeminFlow(QString);
    void editedgemaxFlow(QString);
    void editedgeFlow(QString);
    void editedgeReducedCost(QString); //Klar

    double nodeFlow();
    std::string nodeName();

    double edgeCost(); // Klar
    double edgeminFlow();
    double edgemaxFlow();

    void change_currentnode(GraphicNode*);
    void change_currentedge(GraphicEdge*);

    GraphicNode* return_current_node();
    GraphicEdge* return_current_edge();//

private:
    QLineEdit *nodeName_, *nodeFlow_, *nodePrice_, *edgeCost_, *edgeReducedCost_, *edgeFlow_, *maxFlow_, *minFlow_;
    QPushButton *change_node_info_, *change_edge_info;
    GraphicNode *current_node;
    GraphicEdge *current_edge;
    //Lista med alla noder i interfacet
    //QList<GraphicNode *> nodeList;
    
    
};

#endif // DATADOCK_H
