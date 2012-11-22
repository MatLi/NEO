/* 
 * FILNAMN:          Path.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Representerar en väg mellan två noder i ett nätverk. Ärver från Set<Edge>.
*/

#include "Path.h"

using namespace std;

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

// Sätter startnoden
void
Path::set_start_node(Node* new_start)
{
  start_ = new_start;
}

//Sätter slutnoden
void
Path::set_end_node(Node* new_end)
{
  end_ = new_end;
}

// Tömmer mängden
// ??????????????
