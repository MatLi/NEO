/*
 * FILENAME:      Node.h
 * PROJECT:       NEO
 * PROGRAMMER:    David
 * 
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Node is an object that corresponds to a node in a network problem.
 */

#ifndef NODE_HH
#define NODE_HH

#include "Edge.h"
#include "Set.h"
#include <stack>
#include <string>

class Edge;

class Node
{
 public:
  Node() = default;
  Node(std::string);
  ~Node() = default;

  unsigned int id() const;
  std::string name() const;
  double xpos() const;
  double ypos() const;
  double flow() const;
  double node_price() const;
  Set<Edge*>& in_edges();
  Set<Edge*>& out_edges();
  Set<Edge*>& all_edges();
  bool connected() const;

  void change_id(unsigned int);
  void change_name(std::string);
  void change_xpos(double);
  void change_ypos(double);
  void change_flow(double);
  void change_node_price(double);
  void add_in_edge(Edge*);
  void add_out_edge(Edge*);
  void remove_in_edge(Edge*);
  void remove_out_edge(Edge*);
  void flip_connected();
  void set_connected(bool);
  
  void backup_data();
  void restore_data();

 private:
  unsigned int id_ = 0;
  std::string name_;
  double xpos_;
  double ypos_;
  double flow_;
  double node_price_;
  Set<Edge*> in_edges_;
  Set<Edge*> out_edges_;
  Set<Edge*> all_edges_;
  bool connected_;

  std::stack<double> backup_flow_;
};

#endif
