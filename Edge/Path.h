/* 
 * FILNAMN:          Path.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li,  Linda och Emil
 *
 * DATUM:            2012-11-22
 *
 * BESKRIVNING:
 * Representerar en v�g mellan tv� noder i ett n�tverk. Anv�nder sig av en dubbell�nkad lista f�r att h�lla ordning p� b�garna
*/

#ifndef PATH_HH
#define PATH_HH

#include "Edge.h"
#include "Node.h"
#include <list>

class Path
{
  Path();
  Path(Edge* new_edge_);

  ~Path() = default; // Vi kommer att ta bort list<Edge*> och pekare -> default ok!

  Node* start_node() const;
  Node* end_node() const;
  Edge* start_edge() const;
  void set_start_edge(Edge*);
  void set_end_edge(Edge*);
  
  void clear();

 private:
  Node* start_;
  Node* end_;
  std::list<Edge*> members_;
};

#endif
