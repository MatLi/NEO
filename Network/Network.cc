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

// // Genererar en billigaste-tr�d-l�sning
// // Utg�r fr�n att n�tverket �r "nollst�llt"
// void
// Network::cheapest_tree()
// {
//   //Tempor�ra variabler
//   Node* working_node = nullptr;
//   Edge* Cheapest_current_edge = nullptr;
//   Set<Node*> Searched;
//   Set<Node*> Not_Searched(nodes_);
//   double Cheapest_cost = 1.7*10^308; //Maxv�rde f�r double i C++
//   bool from_in_edges = false;

//   if (nodes_.size()==0)
//   {
//     // n�got slags feluttryck
//     cout << "N�tverket saknar noder" << endl;
//   }
  
//   //V�ljer f�rsta jobbnoden och justerar nodm�ngderna
//   working_node = Not_searched[0];
//   Searched.add_member(working_node);
//   Not_searched.remove_member(working_node);

//   //Loopar �ver alla b�gar som ska v�ljas
//   for (unsigned int edges_in_tree = 1; edges_in_tree <= nodes_.size()-1; edges_in_tree++)
//   {
    
//     //Loopar �ver alla noder i Searched
//     for (unsigned int j=0;j<Searched.size();j++)
//     {
//       //S�tter working_node till iteratornumrets nod
//       working_node = Searched[j];

//       //S�ker igenom working_node:s inb�gar efter billigaste b�ge
//       for(unsigned int i=0; i<working_node->in_edges.size() ; i++)
//       {
// 	// Kollar om b�gen �r m�jligt alternativ
// 	if (working_node->in_edges(i).cost() < Cheapest_cost // Kollar om b�gpriset �r billigast
// 	    && working_node->in_edges(i).flow()==0  // Kollar om b�gen anv�nds
// 	    && Searched.search_element(working_node->in_edges(i)).from_node()==false) // Kollar om fr�n-noden redan finns i m�ngden
// 	{
// 	  Cheapest_cost = working_node->in_edges(i).cost();
// 	  Cheapest_current_edge = working_node->in_edges(i);
// 	  from_in_edges = true;
// 	}
//       }
//       // S�ker igenom working_node:s utb�gar efter billigaste b�ge
//       for(unsigned int i=0; i<working_node->out_edges.size() ; i++)
//       {
// 	// Kollar om b�gen �r m�jligt alternativ
// 	if (working_node->out_edges(i).cost() < Cheapest_cost // Kollar om b�gpriset �r billigast
// 	    && working_node->out_edges(i).flow()==0  // Kollar om b�gen anv�nds
// 	    && Searched.search_element(working_node->out_edges(i)).to_node()==false) // Kollar om till-noden redan finns i m�ngden
// 	{
// 	  Cheapest_cost = working_node->out_edges(i).cost();
// 	  Cheapest_current_edge = working_node->out_edges(i);
// 	  from_in_edges = false;
// 	}
//       }
//     }
  
//     //Uppdaterar n�tverket med ny b�ge i tr�det 
//     Cheapest_current_edge->change_flow() = 1; //b�gen anv�nds i tr�det
  
//     //Uppdaterar nodm�ngder
//     if (from_in_edges == true)
//     {
//       Searched.add_member(Cheapest_current_edge->from_node());
//       Not_Searched.remove_member(Cheapest_current_edge->from_node());
//     }
//     else
//     {
//       Searched.add_member(Cheapest_current_edge->to_node());
//       Not_Searched.remove_member(Cheapest_current_edge->to_node());
//     }

//     //Nollst�ller cheapest:s v�rden
//     Cheapest_cost = 1.7*10^308; //Maxv�rde f�r double i C++
//     Cheapest_current_edge = nullptr;
//   }
// }

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

