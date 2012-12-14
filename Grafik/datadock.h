/* 
 * FILENAME:      datadock.h
 * PROJECT:       NEO
 * PROGRAMMER:    Emil
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Dock window to the right. Information about nodes and edges is given
 * to user. 
 */

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
    void editNodeName(QString);
    void editNodeFlow(QString);
    void editNodePrice(QString);

    void editEdgeCost(QString);
    void editEdgeMinFlow(QString);
    void editEdgeMaxFlow(QString);
    void editEdgeFlow(QString);
    void editEdgeReducedCost(QString);

    double nodeFlow();
    std::string nodeName();

    double edgeCost(); 
    double edgeMinFlow();
    double edgeMaxFlow();

    void changeCurrentNode(GraphicNode*);
    void changeCurrentEdge(GraphicEdge*);

    GraphicNode* returnCurrentNode();
    GraphicEdge* returnCurrentEdge();

private:
    QLineEdit *nodeName_, *nodeFlow_, *nodePrice_, *edgeCost_, *edgeReducedCost_, *edgeFlow_, *maxFlow_, *minFlow_;
    QPushButton *change_node_info_, *change_edge_info;
    GraphicNode *current_node;
    GraphicEdge *current_edge;  
    
};

#endif // DATADOCK_H
