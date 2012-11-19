#ifndef EDGE_HH
#define EDGE_HH

#include "Node.h"

class Edge
{
  Edge() = default; //MÅSTE SKRIVAS OM!
  ~Edge() = default; //MÅSTE SKRIVAS OM!

  Node* from_node() const;
  Node* to_node() const;
  double flow() const;
  void change_flow(double);
  double reduced_cost() const;
  void change_reduced_cost(double);

 private:
  Node* from_;
  Node* to_;
  double flow_;
  double reduced_cost_;
}

#endif
