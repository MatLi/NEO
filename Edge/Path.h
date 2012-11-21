/* 
 * FILNAMN:          Path.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Representerar en v�g mellan tv� noder i ett n�tverk. �rver fr�n Set<Edge>.
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
