#ifndef DATADOCK_H
#define DATADOCK_H

#include <QDockWidget>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QtGui/QGraphicsView>

class DataDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit DataDock(QWidget *parent = 0);

protected:
   // void editLineText(QString *start_node,QString *end_node);

private:
    QGraphicsSimpleTextItem *nodeName_, *nodePrice_, *nodeFlow_;
    QLineEdit *start, *end;
    QPushButton *add_edge_;
    //Lista med alla noder i interfacet
    //QList<GraphicNode *> nodeList;
    
    
};

#endif // DATADOCK_H
