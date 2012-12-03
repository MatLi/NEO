/* 
 * FILNAMN:          Network.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt nätverk av noder och bågar. 
 * Lösningarna till de olika problemen kommer att vara ett Network.  
*/

#ifndef NETWORK_HH
#define NETWORK_HH

#include <string>
#include "Node.h"
#include "Edge.h"
#include "Set.h"

class Network
{
 public:

 Network()
   : edges_(), nodes_() {}

 Network(Set<Node*> in_nodes_, Set<Edge*> in_edges_)
   : edges_(in_edges_), nodes_(in_nodes_) {}

 Network(Set<Node*> in_nodes_)
   : nodes_(in_nodes_) {}
  
  ~Network() = default; // Inga pekare default OK
  
  Set<Edge*> edge_set() const;
  Set<Node*> node_set() const;
  void add_node(Node*);
  void add_edge(Edge*);
  void remove_node(Node*);
  void remove_edge(Edge*);
  void remove_all_edges();
  void remove_all_nodes();
  void reset_network();
  
  //void cheapest_tree();
  void shortest_path(Node*, Node*);
  void min_cost_flow();
  void max_cost_flow();
  void max_flow();

  // Eventuellt?
  //void fwrite(std::string);
  //void fopen(std::string);
  
 private:
  Set<Edge*> edges_;
  Set<Node*> nodes_;
};

#endif
