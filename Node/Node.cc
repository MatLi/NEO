/*
 * Fil: Node.cc
 * Programmerare: David Larsson <davla210>
 * Datum: 2012-11-21
 *
 * Definitioner för klassen Node, som representerar noder i nätverket.
 * Varje nod kan nå sina bågar (såväl in som ut) och kan ha ett flöde (vara
 * källa, sänka eller genomfartsnod). Den har också en grafisk position, som
 * används för export till svg-fil (???).
 */

#include "Edge.h"
#include "Node.h"
#include "Position.h"
#include "Set.h"
#include <string>
using namespace std;

Position
Node::position() const
{
  return graphic_pos_;
}

void
Node::change_position(Position new_pos)
{
  graphic_pos_.move_to(new_pos);
  return;
}

double
Node::flow() const
{
  return flow_;
}

void
Node::change_flow(double new_flow)
{
  flow_ = new_flow;
  return;
}

double
Node::node_price() const
{
  return node_price_;
}

void
Node::change_node_price(double new_node_price)
{
  node_price_ = new_node_price;
  return;
}

string
Node::name() const
{
  return name_;
}

void
Node::change_name(string new_name)
{
  name_ = new_name;
  return;
}

Set<Edge*>&
Node::in_edges()
{
  return in_edges_;
}

Set<Edge*>&
Node::out_edges()
{
  return out_edges_;
}

void
Node::add_in_edge(Edge* new_in_edge)
{
  in_edges_.add_member(new_in_edge);
  return;
}

void
Node::remove_in_edge(Edge* old_in_edge)
{
  in_edges_.remove_member(old_in_edge);
  return;
}

void
Node::add_out_edge(Edge* new_out_edge)
{
  out_edges_.add_member(new_out_edge);
  return;
}

void
Node::remove_out_edge(Edge* old_out_edge)
{
  out_edges_.remove_member(old_out_edge);
  return;
}
