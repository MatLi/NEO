#ifndef NODESET_HH
#define NODESET_HH

#include "Node.h"
#include <vector>

class NodeSet
{
  NodeSet() = default;
  ~NodeSet() = default;

  void add_node(Node);
  void remove_node(Node*);
  void clear();
  Node operator[](unsigned int) const;
  unsigned int size() const;

 private:
  std::vector<Node> nodes_;
}

#endif
