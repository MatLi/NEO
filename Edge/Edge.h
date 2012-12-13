/* 
 * FILENAME:      Edge.h
 * PROJEKT:       NEO
 * PROGRAMMERS:   Li and Linda
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Edge is an object that corresponds to an edge in a network problem.
 */

#ifndef EDGE_HH
#define EDGE_HH

#include "Node.h"
#include <stack>

class Node;

class Edge
{
 public:
  Edge() = delete;
  Edge(Node*, Node*);
  ~Edge();

  Node* from_node() const;
  Node* to_node() const;
  double flow() const;
  double reduced_cost() const;
  double cost() const;
  double maxflow() const;
  double minflow() const;

  void change_from(Node*);
  void change_to(Node*);
  void change_flow(double);
  void change_reduced_cost(double);
  void change_cost(double);
  void change_maxflow(double);
  void change_minflow(double);

  void backup_data();
  void restore_data();

 private:
  Node* from_;
  Node* to_;
  double flow_;
  double reduced_cost_;
  double maxflow_;
  double minflow_;
  double cost_;

  std::stack<double> backup_maxflow_;
  std::stack<double> backup_minflow_;
  std::stack<double> backup_cost_;
};

#endif
