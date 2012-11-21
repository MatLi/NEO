/* 
 * FILNAMN:          Path.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Representerar en väg mellan två noder i ett nätverk. Ärver från Set<Edge>.
*/

#ifndef PATH_HH
#define PATH_HH

#include "Set.h"
#include "Edge.h"
#include "Node.h"

class Path : public Set<Edge>
{
  Path() 
    : start_(nullptr), end_(nullptr) {}

  Path(Node* in_start, Node* in_end)
    : start_(in_start), end_(in_end) {}

  ~Path() = default; // Vi vill inte ta bort noderna, bara pekarna -> default ok!

  Node* start_node() const;
  Node* end_node() const;
  void set_start_node(Node*);
  void set_end_node(Node*);
  virtual void clear() override final;

 private:
  Node* start_;
  Node* end_;
}

#endif
