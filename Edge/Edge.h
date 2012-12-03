/* 
 * FILNAMN:          Edge.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-28
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
  
  Edge(Node* in_from_, Node* in_to_ ); //Skrivs i cc-filen
  
  // Vill vi ha fler konstruktorer? 

  ~Edge();

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
