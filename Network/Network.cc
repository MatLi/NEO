/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li och Linda
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt nätverk av noder och bågar. 
 * Lösningarna till de olika problemen kommer att vara ett Network.    
*/

#include "Network.h"

using namespace std;

//  Returnerar alla bågar/kanter
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

// Lägger till en nod
void
Network::add_node(Node* new_node)
{
  nodes_.add_member(new_node);
}

// Lägger till en båge
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

// Tar bort en båge/kant
void
Network::remove_edge(Edge* del_edge)
{
  edges_.remove_member(del_edge);
}

// Tar bort alla bågar/kanter
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

// // Genererar en billigaste-träd-lösning
// // Utgår från att nätverket är "nollställt"
// void
// Network::cheapest_tree()
// {
//   //Temporära variabler
//   Node* working_node = nullptr;
//   Edge* Cheapest_current_edge = nullptr;
//   Set<Node*> Searched;
//   Set<Node*> Not_Searched(nodes_);
//   double Cheapest_cost = 1.7*10^308; //Maxvärde för double i C++
//   bool from_in_edges = false;

//   if (nodes_.size()==0)
//   {
//     // något slags feluttryck
//   }
  
//   //Väljer första jobbnoden och justerar nodmängderna
//   working_node = Not_searched[0];
//   Searched.add_member(working_node);
//   Not_searched.remove_member(working_node);

//   //Loopar över alla bågar som ska väljas
//   for (unsigned int edges_in_tree = 1; edges_in_tree <= nodes_.size()-1; edges_in_tree++)
//   {
    
//     //Loopar över alla noder i Searched
//     for (unsigned int j=0;j<Searched.size();j++)
//     {
//       //Sätter working_node till iteratornumrets nod
//       working_node = Searched[j];

//       //Söker igenom working_node:s inbågar efter billigaste båge
//       for(unsigned int i=0; i<working_node->in_edges.size() ; i++)
//       {
// 	// Kollar om bågen är möjligt alternativ
// 	if (working_node->in_edges(i).cost() < Cheapest_cost // Kollar om bågpriset är billigast
// 	    && working_node->in_edges(i).flow()==0  // Kollar om bågen används
// 	    && Searched.search_element(working_node->in_edges(i)).from_node()==false) // Kollar om från-noden redan finns i mängden
// 	{
// 	  Cheapest_cost = working_node->in_edges(i).cost();
// 	  Cheapest_current_edge = working_node->in_edges(i);
// 	  from_in_edges = true;
// 	}
//       }
//       // Söker igenom working_node:s utbågar efter billigaste båge
//       for(unsigned int i=0; i<working_node->out_edges.size() ; i++)
//       {
// 	// Kollar om bågen är möjligt alternativ
// 	if (working_node->out_edges(i).cost() < Cheapest_cost // Kollar om bågpriset är billigast
// 	    && working_node->out_edges(i).flow()==0  // Kollar om bågen används
// 	    && Searched.search_element(working_node->out_edges(i)).to_node()==false) // Kollar om till-noden redan finns i mängden
// 	{
// 	  Cheapest_cost = working_node->out_edges(i).cost();
// 	  Cheapest_current_edge = working_node->out_edges(i);
// 	  from_in_edges = false;
// 	}
//       }
//     }
  
//     //Uppdaterar nätverket med ny båge i trädet 
//     Cheapest_current_edge->change_flow() = 1; //bågen används i trädet
  
//     //Uppdaterar nodmängder
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

//     //Nollställer cheapest:s värden
//     Cheapest_cost = 1.7*10^308; //Maxvärde för double i C++
//     Cheapest_current_edge = nullptr;
//   }
// }

// Genererar en kortaste-väg-lösning
void
Network::shortest_path(Node* start_node, Node* end_node)
{
  

  //Din kod här
}

// Genererar minkostnadsflöde
void
Network::min_cost_flow()
{
  //Din kod här
}

// Genererar maxkostnadsflöde
void
Network::max_cost_flow()
{
  //Din kod här
}

// Genererar maxflöde
void
Network::max_flow()
{
  //Din kod här
}

