/* 
 * FILNAMN:          Edge.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Edge är ett objekt som motsvarar bågar/kanter i ett nätverksproblem.   
*/

#ifndef EDGE_HH
#define EDGE_HH

#include "Node.h"

class Edge
{
 Edge(): to_(nullptr), 
    from_(nullptr), 
    flow_(0), 
    reduced_cost_(0),
    maxflow_(0), 
    minflow_(0),
    cost_(0){}

  // Vill vi ha fler konstruktorer? 

 ~Edge() = default; // Vi vill inte ta bort noderna som pekas på, deafult kan användas.

  Node* from_node() const;
  Node* to_node() const;
  double flow() const;
  double reduced_cost() const;
  double cost() const;
  double maxflow() const;
  double minflow() const;

  void change_reduced_cost(double);
  void change_cost(double);
  void change_maxflow(double);
  void change_minflow(double);
  void change_from(Node*);
  void change_to(Node*);
  void change_flow(double);

 private:
  //Datamedlemmar
  Node* from_;
  Node* to_;
  double flow_;
  double reduced_cost_;
  double maxflow_;
  double minflow_;
  double cost_;
}

#endif
