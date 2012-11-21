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
#include "Position.h"
#include "Set.h"
#include <string>

class Node
{
  Node() = default;
  ~Node() = default;

  Position& position() const;
  double flow() const;
  void change_flow(double);
  double node_price() const;
  void change_node_price(double);
  std::string name() const;
  void change_name(std::string);
  Set<Edge>& in_edges();
  Set<Edge>& out_edges();
  void add_in_edge(Edge*);
  void add_out_edge(Edge*);
  void remove_in_edge(Edge*);
  void remove_out_edge(Edge*);

 private:
  Position graphic_pos_;
  double flow_;
  double node_price_;
  Set<Edge> in_edges_;
  Set<Edge> out_edges_;
  std::string name_;
}

#endif
