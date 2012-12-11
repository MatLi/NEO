/* 
 * FILNAMN:          Edge.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-28
 *
 * BESKRIVNING:
 * Edge är ett objekt som motsvarar bågar/kanter i ett nätverksproblem.
*/

#include "Edge.h"
#include <cmath>

using namespace std;

/* Konstruktor, krÃ¤ver att vi har tvÃ¥ noder s
 * bÃ¥gengÃ¥r mellan.
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
 * Returnerar från-nod
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
 * Returnerar bÃ¥gflödet
 */
double 
Edge::flow() const
{
  return flow_;
} 

/* double reduced_cost()
 * Returnerar bÃgens reducerade kostnad
 */
double 
Edge::reduced_cost() const
{
  return reduced_cost_;
}

/* double cost()
 * Returnerar bÃgens kostnad
 */
double 
Edge::cost() const
{
  return cost_;
}

/* double maxflow()
 * Returnerar bÃgens maximala flöde 
 */
double 
Edge::maxflow() const
{
  return maxflow_;
}

/* double minflow()
 * Returnerar bÃgens minimala flöde
 */
double 
Edge::minflow() const
{
  return minflow_;
}

/* void change_reduced_cost(double)
 * Ändrar bÃgens reducerade kostnad
 */
void 
Edge::change_reduced_cost(double new_reduced_cost_)
{
  reduced_cost_ = new_reduced_cost_; 
}

/* void change_cost(double)
 * Ändrar bÃgens kostnad
 */
void 
Edge::change_cost(double new_cost_)
{
  cost_ = new_cost_;
}

/* void change_maxflow(double)
 * Ändrar bÃgens maxflöde
 */
void 
Edge::change_maxflow(double new_maxflow_)
{
  maxflow_ = new_maxflow_;
}

/* void change_minflow(double)
 * Ändrar bÃ¥ens minflöde
 */
void 
Edge::change_minflow(double new_minflow_)
{
  minflow_ = new_minflow_;
}

/* void change_from(Node*)
 * Ändrar bÃgens från-nod
 */
void
Edge::change_from(Node* new_from)
{
  from_->remove_out_edge(this);
  from_ = new_from;
  from_->add_out_edge(this);
}

/* void change_to(Node*)
 * Ändrar bÃgens till-nod
 */
void
Edge::change_to(Node* new_to)
{
  to_->remove_in_edge(this);
  to_ = new_to;
  to_->add_in_edge(this);
}

/* void change_flow(double)
 * Ändrar bÃ¥gens flöd
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
