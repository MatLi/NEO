/* 
 * FILNAMN:          Edge.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Edge �r ett objekt som motsvarar b�gar/kanter i ett n�tverksproblem.   
*/

#ifndef EDGE_HH
#define EDGE_HH

#include "Node.h"

class Node;

class Edge
{
 public:
  Edge() = delete;
  
 Edge(Node* in_from_, Node* in_to_ )
   :to_(in_to_), 
    from_(in_from_), 
    flow_(0), 
    reduced_cost_(0),
    maxflow_(0), 
    minflow_(0),
    cost_(0){}
  
  // Vill vi ha fler konstruktorer? 

 ~Edge() = default; // Vi vill inte ta bort noderna som pekas p�, deafult kan anv�ndas.

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
};

#endif
