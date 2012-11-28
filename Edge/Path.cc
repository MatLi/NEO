/* 
 * FILNAMN:          Path.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, Linda, Emil, David
 *
 * DATUM:            2012-11-22
 *
 * BESKRIVNING:
 * Representerar en v�g mellan tv� noder i ett n�tverk. Anv�nder sig av en dubbell�nkad lista f�r att h�lla ordning p� b�garna
*/

#include "Edge.h"
#include "Node.h"
#include "Path.h"
#include <list>
#include <stdexcept>
#include <iterator>

using namespace std;

// Konstruktor med en specifik b�ge
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

// Returnerar f�rsta b�gen
Edge*
Path::start_edge() const
{
  return members_.front();
}

// Returnerar sista b�gen
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
      throw path_error("Du f�rs�kte s�tta in en b�ge som inte b�rjar i slutnoden eller slutar i begynnelsenoden.");
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

// T�mmer Path 
void
Path::clear()
{
  members_.clear();
}
