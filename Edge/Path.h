/* 
 * FILNAMN:          Path.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li,  Linda och Emil
 *
 * DATUM:            2012-11-22
 *
 * BESKRIVNING:
 * Representerar en väg mellan två noder i ett nätverk. Använder sig av en dubbellänkad lista för att hålla ordning på bågarna
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
