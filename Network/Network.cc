/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, Linda och Jonas
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt nätverk av noder och bågar. 
 * Lösningarna till de olika problemen kommer att vara ett Network.    
*/

#include "Network.h"
#include <iostream>
#include <fstream>
#include <cctype>

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
  delete del_node;
}

// Tar bort en båge/kant
void
Network::remove_edge(Edge* del_edge)
{
  edges_.remove_member(del_edge);
  delete del_edge;
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

/* void reset_network()
 * Återställer algoritmernas genererade data: bågflöden, nodpriser, reducerade
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

// // Genererar en billigaste-träd-lösning
// // Utgår från att nätverket är "nollställt"
// void
// Network::cheapest_tree()
// {
//   //Temporära variabler
//   Node* working_node = nullptr;
//   Set<Node*> Searched;
//   Set<Node*> Not_Searched(nodes_);
//   Set<Edge*> Spanning_Edges;
//   const unsigned int num_nodes = nodes_.size();

//   if (nodes_.empty())
//     {
//       throw network_error("Nätverket saknar noder");
//     }

//   // Initialisera algoritmen.
//   working_node = Not_Searched[0];
//   Searched.add_member(working_node);
//   Not_searched.remove_member(working_node);

//   //Väljer första jobbnoden och justerar nodmängderna
//   do
//     {
//       double min_cost = 1.7*10^308; //Maxvärde för double i C++
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
// 	  throw network_error("Kan ej generera billigaste uppspännande träd, det finns inte kanter till alla noder.");
// 	}
//       else
// 	{
// 	  (*it).change_flow(1); // Tolkas som att kanten är med i BUT.
// 	}
//     }
//   return;
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
	       << "name=\"" << (*it).name() << "\" " // behöver kanske encodas
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
Felutskrift(const char next_char, const string word)
{
  cout << "Fel - " << next_char << " - " << word << endl << endl;
  return;
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
  bool in_network = false;
  bool in_nodes = false;
  bool in_edges = false;
  bool making_node = false;
  bool making_edge = false;
  bool after_nodes = false;
  bool after_edges = false;
  char next_char = ' ';
  while (xmlread.good())
    {
      xmlread.get(next_char);
      if (!xmlread.good())
	{
	  break;
	}

      if (isspace(next_char)) // Space - klar
	{
	  if ((making_tagname and !in_word) or
	      (in_word and !making_tagname and !in_arg))
	    {
	      // Error
	      Felutskrift(next_char,word);
	      break;
	    }
	  else if (making_tagname)
	    {
	      tagname = word;
	      word = "";
	      in_word = false;
	      making_tagname = false;
	      if (tagname == "network")
		{
		  if (in_network)
		    {
		      // Error
		      Felutskrift('*', "network in network");
		      break;
		    }
		  else
		    {
		      in_network = true;
		    }
		}
	      else if (tagname == "nodes")
		{
		  if (!in_network or
		      in_nodes or
		      after_nodes)
		    {
		      
		      // Error
		      Felutskrift('*', "nodes in wrong place");
		      break;
		    }
		  else
		    {
		      in_nodes = true;
		    }
		}
	      else if (tagname == "node")
		{
		  if (!in_nodes)
		    {
		      
		      // Error
		      Felutskrift('*', "node in wrong place");
		      break;
		    }
		  else
		    {
		      making_node = true;
		    }
		}
	      else if (tagname == "edges")
		{
		  if (!in_network or
		      !after_nodes or
		      in_edges or 
		      after_edges)
		    {
		      
		      // Error
		      Felutskrift('*', "edges in wrong place");
		      break;
		    }
		  else
		    {
		      in_edges = true;
		    }
		}
	      else if (tagname == "edge")
		{
		  if (!in_edges)
		    {
		      // Error
		      Felutskrift('*', "edge in wrong place");
		      break;
		    }
		  else
		    {
		      making_edge = true;
		    }
		}
	      else
		{
		  // Error
		  Felutskrift('*', tagname);
		  break;
		  // tillåt okända tags, inte fel?
		  //    flagga in_unknown_tag?
		}
	    }
	  else if (in_arg)
	    {
	      word.push_back(next_char); // ska alla spaces tillåtas?
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
	      Felutskrift(next_char,word);
	      break;
	    }
	  else
	    {
	      in_tag = true;
	      making_tagname = true;
	    }
	}
      else if (next_char == '/') // Endtag
	{
	  if (!in_tag or
	      (in_word and !making_tagname) or
	      arg_expected or
	      in_arg or
	      end_expected)
	    {
	      // Error
	      Felutskrift(next_char,word);
	      break;
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
	      Felutskrift(next_char,word);
	      break;
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
	      Felutskrift(next_char,word);
	      break;
	    }
	  else
	    {
	      in_word = false;
	      label = word;
	      word = "";
	      arg_expected = true;
	      // Kolla redan här om bra label
	    }
	}
      else if (next_char == '\"') // Quote
	{
	  if (!arg_expected and !in_arg)
	    {
	      // Error
	      Felutskrift(next_char,word);
	      break;
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
	      Felutskrift(next_char,word);
	      break;
	    }
	  else
	    {
	      in_tag = false;
	      word = "";
	      in_word = false;
	      end_expected = false;
	      making_tagname = false;
	      // gör det som ska göras, iaf om endtag
	      // om making_tagname - starta in_nånting
	      //     samma koll som space isf
	      // om end_expected - avsluta in_nånting
	    }
	}
      else // Unknown character - klar
	{
	  // Error eller bara skippa
	  Felutskrift(next_char,word);
	  break;
	}
    }
  
  xmlread.close();
}
