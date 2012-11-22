/* 
 * FILNAMN:          Path.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, Linda och Emil
 *
 * DATUM:            2012-11-22
 *
 * BESKRIVNING:
 * Representerar en v�g mellan tv� noder i ett n�tverk. Anv�nder sig av en dubbell�nkad lista f�r att h�lla ordning p� b�garna
*/

#include "Path.h"

using namespace std;

// Defaultkonstruktor
Path::Path()
{
  start_ = nullptr;
  end_   = nullptr;
}

// Konstruktor med en specifik b�ge
Path::Path(Edge* new_edge_)
{
  start_ = new_edge_->from;
  end_   = new_edge_->to;
  
  members_.push_front(new_edge);
}

// Returnerar startnoden
Node*
Path::start_node() const
{
  return start_;
}

// Returnerar slutnoden
Node*
Path::end_node() const
{
  return end_;
}

// Returnerar f�rsta b�gen
Edge*
Path::start_edge() const
{
  return members_.front();
}

// S�tter startnoden
void
Path::set_start_edge(Edge* new_start)
{
  members_.push_front(new_start);
  start_ = new_start->from;
}

// S�tter slutnoden
void
Path::set_end_edge(Edge* new_end)
{
  members_.push_back(new_edge);
  end_   = new_end->to;
}

// T�mmer Path 
void
Path::clear()
{
  start_ = nullptr;
  end_   = nullptr;
  members_.clear();
 }
