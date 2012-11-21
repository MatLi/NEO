/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt n�tverk av noder och b�gar. 
 * L�sningarna till de olika problemen kommer att vara ett Network.    
*/

#include "Network.h"

using namespace std;

//  Returnerar alla b�gar/kanter
Set<Edge>
Network::edge_set() const
{
  return edges_;
}

// Returnerar alla noder
Set<Node>
Network::node_set() const
{
  return nodes_;
}

// L�gger till en nod
void
Network::add_node(Node* new_node)
{
  nodes_.add_member(new_node);
}

// L�gger till en b�ge
void
Network::add_edge(Edge* new_edge)
{
  edges_.add_member(new_edge);
}

// Tar bort en nod
void
Network::remove_node(Node* del_node)
{
  nodes_.remove_member(del_node);
}

// Tar bort en b�ge/kant
void
Network::remove_edge(Edge* del_edge)
{
  edges_.remove_member(del_edge);
}

// Tar bort alla b�gar/kanter
void
Network::remove_all_edges()
{
  edges_.clear();
}

// Tar bort alla noder
void
Network::remove_all_nodes()
{
  nodes_.clear();
}

// Genererar en billigaste-tr�d-l�sning
void
Network::cheapest_tree()
{
  //Din kod h�r
}

// Genererar en kortaste-v�g-l�sning
void
Network::shortest_path(Node* start_node, Node* end_node)
{
  //Din kod h�r
}

// Genererar minkostnadsfl�de
void
Network::min_cost_flow()
{
  //Din kod h�r
}

// Genererar maxkostnadsfl�de
void
Network::max_cost_flow()
{
  //Din kod h�r
}

// Genererar maxfl�de
void
Network::max_flow()
{
  //Din kod h�r
}

