/* 
 * FILNAMN:          Path.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Representerar en v�g mellan tv� noder i ett n�tverk. �rver fr�n Set<Edge>.
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

// S�tter startnoden
void
Path::set_start_node(Node* new_start)
{
  start_ = new_start;
}

//S�tter slutnoden
void
Path::set_end_node(Node* new_end)
{
  end_ = new_end;
}

// T�mmer m�ngden
// ??????????????
