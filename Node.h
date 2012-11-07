#ifndef NODE_HH
#define NODE_HH

#include "Position.h"
#include "EdgeSet.h"

class Node
{
  Node() = default;
  ~Node() = default;

  Position& position() const;
  double flow() const;
  void change_flow(double);
  double node_price() const;
  void change_node_price(double);
  EdgeSet& in_edges();
  EdgeSet& out_edges();

 private:
  Position graphic_pos_;
  double flow_;
  double node_price_;
  EdgeSet in_edges_;
  EdgeSet out_edges_;
}

#endif
