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
#include <iostream>

using namespace std;

//  Returnerar alla b�gar/kanter
Set<Edge*>
Network::edge_set() const
{
  return edges_;
}

// Returnerar alla noder
Set<Node*>
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
  delete del_node;
}

// Tar bort en b�ge/kant
void
Network::remove_edge(Edge* del_edge)
{
  edges_.remove_member(del_edge);
  delete del_edge;
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

/* void reset_network()
 * �terst�ller algoritmernas genererade data: b�gfl�den, nodpriser, reducerade
 * kostnader.
 */
void
Network::reset_network()
{
  for (auto it : edges_)
    {
      (*it).change_flow(0);
      (*it).change_reduced_cost(0);
    }
  for (auto it : nodes_)
    {
      (*it).change_node_price(0);
    }
  return;
}

// Genererar en billigaste-tr�d-l�sning
// Utg�r fr�n att n�tverket �r "nollst�llt"
void
Network::cheapest_tree()
{
  //Tempor�ra variabler
  Node* working_node = nullptr;
  Set<Node*> Searched;
  Set<Node*> Not_Searched(nodes_);
  Set<Edge*> Spanning_Edges;
  const unsigned int num_nodes = nodes_.size();

  if (nodes_.empty())
    {
      throw network_error("N�tverket saknar noder");
    }

  // Initialisera algoritmen.
  working_node = Not_searched[0];
  Searched.add_member(working_node);
  Not_searched.remove_member(working_node);

  //V�ljer f�rsta jobbnoden och justerar nodm�ngderna
  do
    {
      double min_cost = 1.7*10^308; //Maxv�rde f�r double i C++
      Edge* cheapest_current_edge = nullptr;
      for (auto it : edges_)
	{
	  if (Searched.exists((*it).from_node()) &&
	      Not_Searched.exists((*it).to_node()))
	    {
	      if ((*it).cost() < min_cost)
		{
		  cheapest_current_edge = &(*it);
		  min_cost = (*it).cost();
		}
	    }
	}
      Spanning_Edges.add_member(cheapest_current_edge);
      Searched.add_member(cheapest_current_edge->to_node());
      Not_Searched.remove_member(cheapest_current_edge->to_node());
    } while(Spanning_Edges.size() < num_nodes - 1);

  for (auto it : Spanning_Edges)
    {
      if (&(*it) == nullptr)
	{
	  throw network_error("Kan ej generera billigaste uppsp�nnande tr�d, det finns inte kanter till alla noder.");
	}
      else
	{
	  (*it).change_flow(1); // Tolkas som att kanten �r med i BUT.
	}
    }
  return;
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

