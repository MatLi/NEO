#ifndef PATH_HH
#define PATH_HH

#include "EdgeSet.h"
#include "Edge.h"
#include "Node.h"
#include <unordered_set>

class Path : public EdgeSet
{
  Path() = default; // M�STE SKRIVAS OM!
  ~Path() = default; // M�STE SKRIVAS OM!

  Node* start_node();
  Node* end_node();

 private:
  Node* start_;
  Node* end_;
}

#endif
