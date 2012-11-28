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
#include <stdexcept>
#include <iterator>

class path_error: public std::logic_error
{
 public:
  explicit path_error(const std::string &message) noexcept:
  std::logic_error(message) { }
};

class Path
{
 public:
  
 Path(): members_() {}
  Path(Edge* new_edge_);

  ~Path() = default; // Vi kommer att ta bort list<Edge*> -> default ok!

  Node* start_node() const;
  Node* end_node() const;
  Edge* start_edge() const;
  Edge* end_edge() const;
  void insert_edge(Edge*);
  bool empty() const;
  
  std::list<Edge*>::iterator begin();
  std::list<Edge*>::iterator end();
  
  void clear();

 private:
  std::list<Edge*> members_;
};

#endif
