/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, Linda och Jonas
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt n�tverk av noder och b�gar. 
 * L�sningarna till de olika problemen kommer att vara ett Network.    
*/

#include "Network.h"
#include <iostream>
#include <fstream>
#include <cctype>

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

// // Genererar en billigaste-tr�d-l�sning
// // Utg�r fr�n att n�tverket �r "nollst�llt"
// void
// Network::cheapest_tree()
// {
//   //Tempor�ra variabler
//   Node* working_node = nullptr;
//   Set<Node*> Searched;
//   Set<Node*> Not_Searched(nodes_);
//   Set<Edge*> Spanning_Edges;
//   const unsigned int num_nodes = nodes_.size();

//   if (nodes_.empty())
//     {
//       throw network_error("N�tverket saknar noder");
//     }

//   // Initialisera algoritmen.
//   working_node = Not_Searched[0];
//   Searched.add_member(working_node);
//   Not_searched.remove_member(working_node);

//   //V�ljer f�rsta jobbnoden och justerar nodm�ngderna
//   do
//     {
//       double min_cost = 1.7*10^308; //Maxv�rde f�r double i C++
//       Edge* cheapest_current_edge = nullptr;
//       for (auto it : edges_)
// 	{
// 	  if (Searched.exists((*it).from_node()) &&
// 	      Not_Searched.exists((*it).to_node()))
// 	    {
// 	      if ((*it).cost() < min_cost)
// 		{
// 		  cheapest_current_edge = &(*it);
// 		  min_cost = (*it).cost();
// 		}
// 	    }
// 	}
//       Spanning_Edges.add_member(cheapest_current_edge);
//       Searched.add_member(cheapest_current_edge->to_node());
//       Not_Searched.remove_member(cheapest_current_edge->to_node());
//     } while(Spanning_Edges.size() < num_nodes - 1);

//   for (auto it : Spanning_Edges)
//     {
//       if (&(*it) == nullptr)
// 	{
// 	  throw network_error("Kan ej generera billigaste uppsp�nnande tr�d, det finns inte kanter till alla noder.");
// 	}
//       else
// 	{
// 	  (*it).change_flow(1); // Tolkas som att kanten �r med i BUT.
// 	}
//     }
//   return;
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

void
Network::fwrite(const string filename)
{
  ofstream xmlwrite;
  xmlwrite.open(filename);

  xmlwrite << "<network>" << endl;
  xmlwrite << "  <nodes>" << endl;
  for (auto it : nodes_)
    {
      xmlwrite << "    <node "
	       << "id=\"" << it << "\" "
	       << "name=\"" << (*it).name() << "\" " // beh�ver kanske encodas
	       << "xpos=\"" << (*it).position().xpos() << "\" "
	       << "ypos=\"" << (*it).position().ypos() << "\" "
	       << "flow=\"" << (*it).flow() << "\" "
	       << "node_price=\"" << (*it).node_price() << "\" "
	       << "/>" << endl;
    }
  xmlwrite << "  </nodes>" << endl;
  xmlwrite << "  <edges>" << endl;
  for (auto it : edges_)
    {
      xmlwrite << "    <edge "
	       << "flow=\"" << (*it).flow() << "\" "
	       << "reduced_cost=\"" << (*it).reduced_cost() << "\" "
	       << "cost=\"" << (*it).cost() << "\" "
	       << "maxflow=\"" << (*it).maxflow() << "\" "
	       << "minflow=\"" << (*it).minflow() << "\" "
	       << "from_node=\"" << (*it).from_node() << "\" "
	       << "to_node=\"" << (*it).to_node() << "\" "
	       << "/>" << endl;
    }
  xmlwrite << "  </edges>" << endl;
  xmlwrite << "</network>";
 
  xmlwrite.close();
}

void
Network::fopen(const string filename)
{
  ifstream xmlread;
  xmlread.open(filename);
  
  string word;
  string tagname;
  string label;
  bool in_tag = false;
  bool in_word = false;
  bool in_arg = false;
  bool end_expected = false;
  bool arg_expected = false;
  bool making_tagname = false;
  char next_char = ' ';
  while (xmlread.good())
    {
      xmlread >> next_char;

      if (isspace(next_char)) // Space - klar
	{
	  if ((making_tagname and !in_word) or
	      (in_word and !making_tagname and !in_arg))
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerad space" << endl;
	    }
	  else if (making_tagname)
	    {
	      tagname = word;
	      word = "";
	      in_word = false;
	      making_tagname = false;
	      // Kolla om bra tagname
	    }
	  else if (in_arg)
	    {
	      word.push_back(next_char);
	    }
	  else
	    {
	      continue;
	    }
	}
      else if (next_char == '<') // Start tag - klar
	{
	  if (in_tag)
	    {
	      // ERROR
	      cout << "Inl�sningsfel - felplacerad <" << endl;
	    }
	  else
	    {
	      in_tag = true;
	      making_tagname = true;
	    }
	}
      else if (next_char == '/') // Endtag - klar
	{
	  if (!in_tag or
	      (in_word and !making_tagname) or
	      arg_expected or
	      in_arg or
	      end_expected)
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerad /" << endl;
	    }
	  else
	    {
	      end_expected = true;
	      in_word = false;
	      // det blir inge bra om typ <tagname/> - inte bra
	    }
	}
      else if (isalnum(next_char) or
	       next_char == '_') // Alph or Num - klar
	{
	  if (!in_tag or
	      arg_expected or
	      (end_expected and !making_tagname))
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerat tecken" << endl;
	    }
	  else if (in_word)
	    {
	      word.push_back(next_char);
	    }
	  else
	    {
	      in_word = true;
	      word = next_char;
	    }
	}
      else if (next_char == '=') // Equal
	{
	  if (!in_word or
	      making_tagname or
	      in_arg)
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerad =" << endl;
	    }
	  else
	    {
	      in_word = false;
	      label = word;
	      word = "";
	      arg_expected = true;
	      // Kolla redan h�r om bra label
	    }
	}
      else if (next_char == '\"') // Quote
	{
	  if (!arg_expected and !in_arg)
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerad \"" << endl;
	    }
	  else
	    {
	      if (arg_expected)
		{
		  in_arg = true;
		  arg_expected = false;
		}
	      else
		{
		  in_arg = false;
		  in_word = false;
		  // fixa grejer
		}
	    }
	}
      else if (next_char == '>') // end of tag
	{
	  if (!in_tag or
	      (!in_word and making_tagname) or
	      (in_word and !making_tagname) or
	      arg_expected or
	      in_arg)
	    {
	      // Error
	      cout << "Inl�sningsfel - felplacerad >" << endl;
	    }
	  else
	    {
	      in_tag = false;
	      // g�r det som ska g�ras, iaf om endtag
	    }
	}
      else // Unknown character - klar
	{
	  // Error eller bara skippa
	  cout << "Kanske inl�sningsfel - ok�nt tecken: " << next_char << endl;
	}
    }
  
  xmlread.close();
}
