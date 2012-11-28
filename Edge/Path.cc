/* 
 * FILNAMN:          Path.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, Linda, Emil, David
 *
 * DATUM:            2012-11-22
 *
 * BESKRIVNING:
 * Representerar en väg mellan två noder i ett nätverk. Använder sig av en dubbellänkad lista för att hålla ordning på bågarna
*/

#include "Edge.h"
#include "Node.h"
#include "Path.h"
#include <list>
#include <stdexcept>
#include <iterator>

using namespace std;

// Konstruktor med en specifik båge
Path::Path(Edge* new_edge_)
{
  members_.push_front(new_edge_);
}

// Returnerar startnoden
Node*
Path::start_node() const
{
  return members_.front()->from_node();
}

// Returnerar slutnoden
Node*
Path::end_node() const
{
  return members_.back()->to_node();
}

// Returnerar första bågen
Edge*
Path::start_edge() const
{
  return members_.front();
}

// Returnerar sista bågen
Edge*
Path::end_edge() const
{
  return members_.back();
}

bool
Path::empty() const
{
  return members_.empty();
}

void
Path::insert_edge(Edge* in_edge)
{
  if (empty())
    {
      members_.push_front(in_edge);
    }
  else if (in_edge->to_node() == start_node())
    {
      members_.push_front(in_edge);
      return;
    }
  else if (in_edge->from_node() == end_node())
    {
      members_.push_back(in_edge);
    }
  else
    {
      throw path_error("Du försökte sätta in en båge som inte börjar i slutnoden eller slutar i begynnelsenoden.");
    }
}

list<Edge*>::iterator
Path::begin()
{
  return members_.begin();
}

list<Edge*>::iterator
Path::end()
{
  return members_.end();
}

// Tömmer Path 
void
Path::clear()
{
  members_.clear();
}
