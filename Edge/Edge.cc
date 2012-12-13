/* 
 * FILENAME:      Edge.cc
 * PROJEKT:       NEO
 * PROGRAMMERS:   Li and Linda
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Edge is an object that corresponds to an edge in a network problem.
 */

#include "Edge.h"
#include <cmath>
using namespace std;

Edge::Edge(Node* in_from, Node* in_to)
  : from_(in_from),
    to_(in_to),
    flow_(0), 
    reduced_cost_(0),
    maxflow_(pow(10,308)), 
    minflow_(0),
    cost_(0),
    backup_maxflow_(),
    backup_minflow_(),
    backup_cost_()
{
  to_->add_in_edge(this);
  from_->add_out_edge(this);
}

Edge::~Edge()
{
  to_->remove_in_edge(this);
  from_->remove_out_edge(this);
}

Node* 
Edge::from_node() const
{
  return from_;
}

Node* 
Edge::to_node() const
{
  return to_;
}

double 
Edge::flow() const
{
  return flow_;
} 

double 
Edge::reduced_cost() const
{
  return reduced_cost_;
}

double 
Edge::cost() const
{
  return cost_;
}

double 
Edge::maxflow() const
{
  return maxflow_;
}

double 
Edge::minflow() const
{
  return minflow_;
}

void 
Edge::change_reduced_cost(double new_reduced_cost)
{
  reduced_cost_ = new_reduced_cost;
  return;
}

void 
Edge::change_cost(double new_cost)
{
  cost_ = new_cost;
  return;
}

void 
Edge::change_maxflow(double new_maxflow)
{
  maxflow_ = new_maxflow;
  return;
}

void 
Edge::change_minflow(double new_minflow)
{
  minflow_ = new_minflow;
  return;
}

void
Edge::change_from(Node* new_from)
{
  from_->remove_out_edge(this);
  from_ = new_from;
  from_->add_out_edge(this);
  return;
}

void
Edge::change_to(Node* new_to)
{
  to_->remove_in_edge(this);
  to_ = new_to;
  to_->add_in_edge(this);
  return;
}

void 
Edge::change_flow(double new_flow)
{
  flow_ = new_flow;
  return;
}

void
Edge::backup_data()
{
  backup_maxflow_.push(maxflow_);
  backup_minflow_.push(minflow_);
  backup_cost_.push(cost_);
  return;
}

void
Edge::restore_data()
{
  maxflow_ = backup_maxflow_.top();
  minflow_ = backup_minflow_.top();
  cost_ = backup_cost_.top();
  backup_maxflow_.pop();
  backup_minflow_.pop();
  backup_cost_.pop();
  return;
}
