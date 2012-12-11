//Mari

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

class GraphicNode;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    //void newNode(Node *node);

public slots:
   // void shuffle();
    //void zoomIn();
  //  void zoomOut();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    //void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    //void scaleView(qreal scaleFactor);

private:
    int timerId;
    GraphicNode *centerNode;
    GraphicNode *node10;
};
//! [0]

#endif
