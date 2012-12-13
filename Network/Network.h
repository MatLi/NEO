/* 
 * FILENAME:      Network.h
 * PROJEKT:       NEO
 * PROGRAMMERS:   Li and  Linda
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Network represents a network of nodes and edges.
 * The solution to a problem will be a Network. 
*/

#ifndef NETWORK_HH
#define NETWORK_HH

#include <deque>
#include <string>
#include <stdexcept>
#include "Node.h"
#include "Edge.h"
#include "Set.h"

class network_error: public std::logic_error
{
 public:
  explicit network_error(const std::string &message) noexcept
    : std::logic_error(message) { }
};

class Network
{
 public:
  Network();
  Network(Set<Node*>, Set<Edge*>);
  Network(Set<Node*>);
  ~Network() = default; // Inga pekare default OK
  
  Set<Edge*> edge_set() const;
  Set<Node*> node_set() const;

  void add_node(Node*);
  void add_edge(Edge*);
  void remove_node(Node*);
  void remove_edge(Edge*);
  void remove_all_nodes();
  void remove_all_edges();
  void reset_network();
  
  void cheapest_tree();
  void cheapest_path(Node*, Node*);
  void min_cost_flow();
  void max_cost_flow();
  void max_flow();
  double flowcost();

  bool fwrite(const std::string);
  bool fopen(const std::string);
  
 private:
  Set<Node*> nodes_;
  Set<Edge*> edges_;
  
  double min_cost_flow_phase2(Set<Edge*>, Set<Edge*>);
  void find_base_and_non_base_edges(Set<Edge*>&, Set<Edge*>&);
  void update_node_prices(Node*, Set<Edge*>);
  void calculate_reduced_costs(Set<Edge*>);
  std::deque<Edge*> find_cycle(Set<Edge*>, Edge*, Node*&);
  std::deque<Edge*> find_cycle_help(std::deque<Edge*>, Set<Edge*>,
				    Node*, Node*);
  bool exists(std::deque<Edge*>, Edge*);
  bool optimal_mincostflow(Set<Edge*>&, Set<Edge*>);
  Edge* find_incoming_edge(Set<Edge*>);
  double find_flow_change_outgoing_edge(std::deque<Edge*>, Node*, Edge*&);
  void change_flow(std::deque<Edge*>, Node*, double);
};

#endif
