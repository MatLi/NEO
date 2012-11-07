#ifndef EDGESET_HH
#define EDGESET_HH

#include "Edge.h"
#include <vector>

class EdgeSet
{
  EdgeSet() = default;
  ~EdgeSet() = default;

  void add_edge(Edge);
  void remove_edge(Edge*);
  void clear();
  Edge operator[](unsigned int) const;
  unsigned int size() const;

 private:
  std::vector<Edge> edges_;
}

#endif
