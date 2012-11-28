/*
 * Fil: Node.h
 * Programmerare: David Larsson <davla210>
 * Datum: 2012-11-21
 *
 * Deklaration av klassen Node, som representerar noder i nätverket.
 * Varje nod kan nå sina bågar (såväl in som ut) och kan ha ett flöde (vara
 * källa, sänka eller genomfartsnod). Den har också en grafisk position, som
 * används för export till svg-fil (???).
 */

#ifndef NODE_HH
#define NODE_HH

#include "Edge.h"
#include "Position.h"
#include "Set.h"
#include <string>

class Edge;

class Node
{
 public:
  Node() = default;
 Node(std::string in_name) : graphic_pos_(), flow_(0), node_price_(0), in_edges_(), out_edges_(), name_(in_name) { }
  ~Node() = default;

  Position position() const;
  void change_position(Position);
  double flow() const;
  void change_flow(double);
  double node_price() const;
  void change_node_price(double);
  std::string name() const;
  void change_name(std::string);
  Set<Edge*>& in_edges();
  Set<Edge*>& out_edges();
  void add_in_edge(Edge*);
  void add_out_edge(Edge*);
  void remove_in_edge(Edge*);
  void remove_out_edge(Edge*);

 private:
  Position graphic_pos_;
  double flow_;
  double node_price_;
  Set<Edge*> in_edges_;
  Set<Edge*> out_edges_;
  std::string name_;
};

#endif
