/* 
 * FILNAMN:          Edge.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-28
 *
 * BESKRIVNING:
 * Edge �r ett objekt som motsvarar b�gar/kanter i ett n�tverksproblem.
*/

#include "Edge.h"
#include <cmath>

using namespace std;

/* Konstruktor, kräver att vi har två noder s
 * bågengår mellan.
 */
Edge::Edge(Node* in_from_, Node* in_to_ )
  : from_(in_from_),
    to_(in_to_),
    flow_(0), 
    reduced_cost_(0),
    maxflow_(pow(10,380)), 
    minflow_(0),
    cost_(0)
{
  to_->add_in_edge(this);
  from_->add_out_edge(this);
}

Edge::~Edge()
{
  to_->remove_in_edge(this);
  from_->remove_out_edge(this);
}

/* Node* from_node()
 * Returnerar fr�n-nod
 */
Node* 
Edge::from_node() const
{
  return from_;
}

/* Node* to_node()
 * Returnerar till-nod
 */
Node* 
Edge::to_node() const
{
  return to_;
}

/* double flow()
 * Returnerar bågfl�det
 */
double 
Edge::flow() const
{
  return flow_;
} 

/* double reduced_cost()
 * Returnerar b�gens reducerade kostnad
 */
double 
Edge::reduced_cost() const
{
  return reduced_cost_;
}

/* double cost()
 * Returnerar b�gens kostnad
 */
double 
Edge::cost() const
{
  return cost_;
}

/* double maxflow()
 * Returnerar b�gens maximala fl�de 
 */
double 
Edge::maxflow() const
{
  return maxflow_;
}

/* double minflow()
 * Returnerar b�gens minimala fl�de
 */
double 
Edge::minflow() const
{
  return minflow_;
}

/* void change_reduced_cost(double)
 * �ndrar b�gens reducerade kostnad
 */
void 
Edge::change_reduced_cost(double new_reduced_cost_)
{
  reduced_cost_ = new_reduced_cost_; 
}

/* void change_cost(double)
 * �ndrar b�gens kostnad
 */
void 
Edge::change_cost(double new_cost_)
{
  cost_ = new_cost_;
}

/* void change_maxflow(double)
 * �ndrar b�gens maxfl�de
 */
void 
Edge::change_maxflow(double new_maxflow_)
{
  maxflow_ = new_maxflow_;
}

/* void change_minflow(double)
 * �ndrar båens minfl�de
 */
void 
Edge::change_minflow(double new_minflow_)
{
  minflow_ = new_minflow_;
}

/* void change_from(Node*)
 * �ndrar b�gens fr�n-nod
 */
void
Edge::change_from(Node* new_from)
{
  from_->remove_out_edge(this);
  from_ = new_from;
  from_->add_out_edge(this);
}

/* void change_to(Node*)
 * �ndrar b�gens till-nod
 */
void
Edge::change_to(Node* new_to)
{
  to_->remove_in_edge(this);
  to_ = new_to;
  to_->add_in_edge(this);
}

/* void change_flow(double)
 * �ndrar bågens fl�d
 */
void 
Edge::change_flow(double new_flow_)
{
  flow_ = new_flow_;
}

void
Edge::backup_data()
{
  backup_maxflow_ = maxflow_;
  backup_minflow_ = minflow_;
  backup_cost_ = cost_;
  return;
}

void
Edge::restore_data()
{
  maxflow_ = backup_maxflow_;
  minflow_ = backup_minflow_;
  cost_ = backup_cost_;
}
