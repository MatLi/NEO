/*
 * FILENAME:      addedgedock.h
 * PROJEKT:       NEO
 * PROGRAMMERS:   Emil, Mari, Li och Linda
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Creating the dock to the right in the window where you can add/remove 
 * edges and remove nodes.
 */

#ifndef ADDEDGEDOCK_H
#define ADDEDGEDOCK_H

#include <QDockWidget>
#include <QGraphicsSimpleTextItem>
#include <QLineEdit>
#include <QPushButton>

class AddEdgeDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit AddEdgeDock(QWidget *parent = 0);
    QString start_text();
    QString end_text();
    QString node_text();


private:
    QLineEdit *start, *end, *node;
    QPushButton *add_edge_, *remove_edge_, *remove_node;

};

#endif // ADDEDGEDOCK_H
