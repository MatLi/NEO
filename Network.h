#ifndef NETWORK_HH
#define NETWORK_HH

#include <string>
#include "Node.h"
#include "NodeSet.h"
#include "Edge.h"
#include "EdgeSet.h"

class Network
{
 public:
  Network() = default;
  ~Network() = default;
  
  EdgeSet edge_set() const;
  NodeSet node_set() const;
  void add_node(Node);
  void add_edge(Edge);
  void remove_node(Node*);
  void remove_edge(Edge*);
  void remove_all_edges();
  void remove_all_nodes();
  
  void cheapest_tree();
  void shortest_path(Node*, Node*);
  void min_cost_flow();
  void max_cost_flow();
  void max_flow();

  void fwrite(std::string);
  void fopen(std::string);
  
 private:
  EdgeSet edges_;
  NodeSet nodes_;
}

#endif
