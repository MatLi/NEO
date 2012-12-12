/*
 * Fil: Node.h
 * Programmerare: David Larsson <davla210>
 * Datum: 2012-11-21
 *
 * Deklaration av klassen Node, som representerar noder i n�tverket.
 * Varje nod kan n� sina b�gar (s�v�l in som ut) och kan ha ett fl�de (vara
 * k�lla, s�nka eller genomfartsnod). Den har ocks� en grafisk position, som
 * anv�nds f�r export till svg-fil (???).
 */

#ifndef NODE_HH
#define NODE_HH

#include "Edge.h"
#include "Set.h"
#include <stack>
#include <string>

class Edge;

class Node
{
 public:
  Node() = default;
 Node(std::string in_name) : xpos_(0), ypos_(0), flow_(0), node_price_(0), in_edges_(), out_edges_(), all_edges_(), name_(in_name), connected_(false), backup_flow_() { }
  ~Node() = default;

  double xpos() const;
  double ypos() const;
  void change_xpos(double);
  void change_ypos(double);
  double flow() const;
  void change_flow(double);
  double node_price() const;
  void change_node_price(double);
  std::string name() const;
  void change_name(std::string);
  Set<Edge*>& in_edges();
  Set<Edge*>& out_edges();
  Set<Edge*>& all_edges();
  void add_in_edge(Edge*);
  void add_out_edge(Edge*);
  void remove_in_edge(Edge*);
  void remove_out_edge(Edge*);
  
  bool connected() const;
  void flip_connected();
  void set_connected(bool);
  
  void backup_data();
  void restore_data();

  unsigned int id() const;
  void change_id(unsigned int);

 private:
  double xpos_;
  double ypos_;
  double flow_;
  double node_price_;
  Set<Edge*> in_edges_;
  Set<Edge*> out_edges_;
  Set<Edge*> all_edges_;
  std::string name_;
  bool connected_;

  std::stack<double> backup_flow_;

  unsigned int id_=0;
};

#endif
