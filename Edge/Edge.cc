/* 
 * FILNAMN:          Edge.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Edge är ett objekt som motsvarar bågar/kanter i ett nätverksproblem.
*/

#include "Edge.h"

using namespace std;

//Konstruktor
Edge::Edge(Node* in_from_, Node* in_to_ )
{
  to_ = in_to_; 
  from_ = in_from_; 
  flow_ = 0; 
  reduced_cost_ = 0;
  maxflow_ = 0; 
  minflow_ = 0;
  cost_ = 0;

  to_->add_in_edge(this);
 from_->add_out_edge(this);
}

// Returnerar från-nod
Node* 
Edge::from_node() const
{
  return from_;
}

//Returnerar till-nod
Node* 
Edge::to_node() const
{
  return to_;
}

// Returnerar flödet
double 
Edge::flow() const
{
  return flow_;
} 

// Returnerar den reducerade kostnaden
double 
Edge::reduced_cost() const
{
  return reduced_cost_;
}

// Returnerar maximala flödet 
double 
Edge::maxflow() const
{
  return maxflow_;
}

// Returnerar minimala flödet
double 
Edge::minflow() const
{
  return minflow_;
}

// Ändrar reducerad kostnad
void 
Edge::change_reduced_cost(double new_reduced_cost_)
{
  reduced_cost_ = new_reduced_cost_; 
}

// Ändrar kostnaden
void 
Edge::change_cost(double new_cost_)
{
  cost_ = new_cost_;
}

// Ändrar maxflöde
void 
Edge::change_maxflow(double new_maxflow_)
{
  maxflow_ = new_maxflow_;
}

// Ändrar minflöde
void 
Edge::change_minflow(double new_minflow_)
{
  minflow_ = new_minflow_;
}

// Ändrar från-nod
void
Edge::change_from(Node* new_from)
{
  from_->remove_out_edge(this);
  from_ = new_from;
  from_->add_out_edge(this);
}

// Ändrar till-nod
void
Edge::change_to(Node* new_to)
{
  to_->remove_in_edge(this);
  to_ = new_to;
  to_->add_in_edge(this);
}

// Ändrar flödet
void 
Edge::change_flow(double new_flow_)
{
  flow_ = new_flow_;
}
