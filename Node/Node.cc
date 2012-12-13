/*
 * FILENAME:      Node.cc
 * PROJECT:       NEO
 * PROGRAMMER:    David
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Node is an object that corresponds to a node in a network problem.
 */

#include "Edge.h"
#include "Node.h"
#include "Set.h"
#include <stack>
#include <string>
using namespace std;

Node::Node(string in_name)
  : name_(in_name),
    xpos_(0),
    ypos_(0),
    flow_(0),
    node_price_(0),
    in_edges_(),
    out_edges_(),
    all_edges_(),
    connected_(false),
    backup_flow_() {}

bool
Node::connected() const
{
  return connected_;
}

void
Node::flip_connected()
{
  connected_ = !connected_;
  return;
}

void
Node::set_connected(bool new_c)
{
  connected_ = new_c;
  return;
}

double
Node::xpos() const
{
  return xpos_;
}

double
Node::ypos() const
{
  return ypos_;
}

void
Node::change_xpos(double new_xpos)
{
  xpos_ = new_xpos;
  return;
}

void
Node::change_ypos(double new_ypos)
{
  ypos_ = new_ypos;
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

Set<Edge*>&
Node::all_edges()
{
  return all_edges_;
}

void
Node::add_in_edge(Edge* new_in_edge)
{
  in_edges_.add_member(new_in_edge);
  all_edges_.add_member(new_in_edge);
  return;
}

void
Node::remove_in_edge(Edge* in_edge)
{
  in_edges_.remove_member(in_edge);
  all_edges_.remove_member(in_edge);
  return;
}

void
Node::add_out_edge(Edge* new_out_edge)
{
  out_edges_.add_member(new_out_edge);
  all_edges_.add_member(new_out_edge);
  return;
}

void
Node::remove_out_edge(Edge* out_edge)
{
  out_edges_.remove_member(out_edge);
  all_edges_.add_member(out_edge);
  return;
}

void
Node::backup_data()
{
  backup_flow_.push(flow_);
  return;
}

void
Node::restore_data()
{
  flow_ = backup_flow_.top();
  backup_flow_.pop();
  return;
}

unsigned int
Node::id() const
{
  return id_;
}

void
Node::change_id(unsigned int new_id)
{
  id_=new_id;
  return;
}
