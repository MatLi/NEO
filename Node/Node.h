#ifndef NODE_HH
#define NODE_HH

#include "Position.h"
#include "Set.h"

class Node
{
  Node() = default;
  ~Node() = default;

  Position& position() const;
  double flow() const;
  void change_flow(double);
  double node_price() const;
  void change_node_price(double);
  Set<Edge>& in_edges();
  Set<Edge>& out_edges();

 private:
  Position graphic_pos_;
  double flow_;
  double node_price_;
  Set<Edge> in_edges_;
  Set<Edge> out_edges_;
}

#endif
