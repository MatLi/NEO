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


// --------------------------
// Filutskrift och -inläsning
// --------------------------


void
Network::fwrite(const string filename)
{
  ofstream xmlwrite;
  xmlwrite.open(filename);
  unsigned int i=0;

  xmlwrite << "<network number_of_nodes=\"" << nodes_.size() << "\">" << endl;
  xmlwrite << "  <nodes>" << endl;
  for (auto it : nodes_)
    {
      (*it).change_id(i++);
      xmlwrite << "    <node "
	       << "id=\"" << (*it).id() << "\" "
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
	       << "from_node=\"" << (*it).from_node()->id() << "\" "
	       << "to_node=\"" << (*it).to_node()->id() << "\" "
	       << "/>" << endl;
    }
  xmlwrite << "  </edges>" << endl;
  xmlwrite << "</network>";
 
  xmlwrite.close();
}

class readstate
{
  string word;
  string tagname;
  string label;
  int int_val = 0;
  double double_val = 0;
  bool in_tag = false;
  bool in_word = false;
  bool in_arg = false;
  bool end_expected = false;
  bool arg_expected = false;
  bool arg_ended = false;
  bool making_tagname = false;
  bool in_network = false;
  bool in_nodes = false;
  bool in_edges = false;
  bool making_node = false;
  bool making_edge = false;
  bool after_nodes = false;
  bool after_edges = false;
  char next_char = ' ';

  void
  space() // "klar"
  {
    if ((making_tagname and !in_word) or
	(in_word and !making_tagname and !in_arg))
      {
	throw network_error("malplaced space");
      }

    if (making_tagname)
      {
	tagname = word;
	word = "";
	in_word = false;
	making_tagname = false;
	if (tagname == "network")
	  {
	    if (in_network)
	      {
		throw network_error("can't place network in network");
	      }

	    in_network = true; // sätta detta här eller i endtag?
	  }
	else if (tagname == "nodes")
	  {
	    if (!in_network or
		in_nodes or
		after_nodes)
	      {
		throw network_error("malplaced nodes tag");
	      }

	    in_nodes = true; // sätta detta här eller i endtag?
	  }
	else if (tagname == "node")
	  {
	    if (!in_nodes)
	      {
		throw network_error("malplaced node tag");
	      }

	    making_node = true;
	  }
	else if (tagname == "edges")
	  {
	    if (!in_network or
		!after_nodes or
		in_edges or 
		after_edges)
	      {
		throw network_error("malplaced edges tag");
	      }

	    in_edges = true; // sätta detta här eller i endtag?
	  }
	else if (tagname == "edge")
	  {
	    if (!in_edges)
	      {
		throw network_error("malplaced edge tag");
	      }

	    making_edge = true;
	  }
	else
	  {
	    // Error?
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
	// Här behöver inget göras
      }
  }

  void
  start_tag() // klar
  {
    if (in_tag)
      {
	throw network_error("can't start a tag in a tag");
      }

    in_tag = true;
    making_tagname = true;
  }

  void
  slash() // "klar"
  {
    if (!in_tag or
	(in_word and !making_tagname) or
	arg_expected or
	in_arg or
	end_expected)
      {
	throw network_error("malplaced slash");
      }

    end_expected = true;
    if (in_word)
      {
	in_word = false;
	making_tagname = false;
	tagname = word;
	word = "";
      }
  }

  void
  alnum() // klar
  {
    if (!in_tag or
	arg_expected or
	(end_expected and !making_tagname))
      {
	throw network_error("malplaced letter, numeral or underscore");
      }
    
    if (in_word)
      {
	word.push_back(next_char);
      }
    else
      {
	in_word = true;
	word = next_char;
      }
  }

  void
  equal()
  {
    if (!in_word or
	making_tagname or
	in_arg)
      {
	throw network_error("malplaced equality sign");
      }
    
    in_word = false;
    label = word;
    word = "";
    arg_expected = true;
    if (making_node)
      {
	if (label == "id") {}
	else if (label == "name") {}
	else if (label == "xpos") {}
	else if (label == "ypos") {}
	else if (label == "flow") {}
	else if (label == "node_price") {}
	else
	  {
	    throw network_error("label \"" + label + "\" not allowed in node");
	  }
      }
    else if (making_edge)
      {
	if (label == "flow") {}
	else if (label == "reduced_cost") {}
	else if (label == "cost") {}
	else if (label == "maxflow") {}
	else if (label == "minflow") {}
	else if (label == "from_node") {}
	else if (label == "to_node") {}
	else
	  {
	    throw network_error("label \"" + label + "\" not allowed in edge");
	  }
      }
    else if (tagname == "network")
      {
	if (label == "number_of_nodes") {}
	else
	  {
	    throw network_error("label \""+label+"\" not allowed in network");
	  }
      }
    else
      {
	throw network_error("malplaced equality sign");
      }
  }
  
  void
  quote()
  {
    if (!arg_expected and !in_arg)
      {
	throw network_error("malplaced quotation sign");
      }

    if (arg_expected)
      {
	in_arg = true;
	arg_expected = false;
      }
    else
      {
	if (!arg_ended and !in_word)
	  {
	    throw network_error("empty argument");
	  }
	
	in_arg = false;
	arg_ended = false;
	in_word = false;
	// fixa grejer
      }
  }

  void
  end_tag()
  {
    if (!in_tag or
	(!in_word and making_tagname) or
	(in_word and !making_tagname) or
	arg_expected or
	in_arg)
      {
	throw network_error("malplaced \">\"");
      }

    in_tag = false;
    if (making_tagname)
      {
	tagname = word;
	word = "";
	in_word = false;
	making_tagname = false;
	if (tagname == "network")
	  {
	    if (!end_expected)
	      {
		throw network_error("must state number of nodes in network");
	      }
	    else if (!in_network)
	      {
		throw network_error("can't end network unless in network");
	      }
	    
	    in_network = false;
	    end_expected = false;
	  }
	else if (tagname == "nodes")
	  {
	    if (!in_network or
		in_nodes == !end_expected or
		after_nodes)
	      {
		throw network_error("malplaced nodes tag");
	      }
	    
	    if (!end_expected)
	      {
		in_nodes = true;
	      }
	    else
	      {
		in_nodes = false;
		after_nodes = true;
	      }
	  }
	else if (tagname == "node")
	  {     
	    throw network_error("node requires data");
	  }
	else if (tagname == "edges")
	  {
	    if (!in_network or
		!after_nodes or
		in_edges == !end_expected or 
		after_edges)
	      {
		throw network_error("malplaced edges tag");
	      }
	    
	    if (!end_expected)
	      {
		in_edges = true;
	      }
	    else
	      {
		in_edges = false;
		after_edges = true;
	      }
	  }
	else if (tagname == "edge")
	  {
	    throw network_error("edge requires data");
	  }
	else
	  {
	    // Error?
	    // tillåt okända tags, inte fel?
	    //    flagga in_unknown_tag?
	  }
      }
    else if (end_expected)
      {
	// gör saker
	making_node = false;
	making_edge = false;
      }
    else
      {
	// networkdeklaration och ev. oavslutad tag
      }
    in_tag = false;
    word = "";
    in_word = false;
    end_expected = false;
    // gör det som ska göras, iaf om endtag
    // om making_tagname - starta in_nånting
    //     samma koll som space isf
    // om end_expected - avsluta in_nånting
  }

public:

  void
  step(const char next)
  {
    next_char = next;
    
    if (isspace(next_char)) // Space
      {
	space();
      }
    else if (next_char == '<') // Start tag
      {
	start_tag();
      }
    else if (next_char == '/') // Slash
      {
	slash();
      }
    else if (isalnum(next_char) or
	     next_char == '_') // Alph or Num
      {
	alnum();
      }
    else if (next_char == '=') // Equal
      {
	equal();
      }
    else if (next_char == '\"') // Quote
      {
	quote();
      }
    else if (next_char == '>') // end of tag
      {
	end_tag();
      }
    else // Unknown character
      {
	// Error eller bara skippa
      }
  }
  void
  step(const int val)
  {
    int_val = val;
    arg_ended = true;
  }
  void
  step(const double val)
  {
    double_val = val;
    arg_ended = true;
  }

  bool
  read_int()
  {
    return (in_arg and
	    !arg_ended and
	    (label == "number_of_nodes" or
	     label == "id" or
	     label == "from_node" or
	     label == "to_node"));
  }
  bool read_double()
  {
    return (in_arg and
	    !arg_ended and
	    (label == "xpos" or
	     label == "ypos" or
	     label == "flow" or
	     label == "node_price" or
	     label == "reduced_cost" or
	     label == "cost" or
	     label == "maxflow" or
	     label == "minflow"));
  }

  // bara för testning
  void
  print()
  {
    cout //<< endl
      << " - word: " << word //<< endl
      << " - tagname: " << tagname //<< endl
      << " - label: " << label //<< endl
      << " - in_tag: " << in_tag //<< endl
      << " - in_word: " << in_word //<< endl
      << " - in_arg: " << in_arg //<< endl
      << " - end_exp: " << end_expected //<< endl
      << " - arg_exp: " << arg_expected //<< endl
      << " - mk_tagname: " << making_tagname //<< endl
      << " - in_network: " << in_network //<< endl
      << " - in_nodes: " << in_nodes //<< endl
      << " - in_edges: " << in_edges //<< endl
      << " - mk_node: " << making_node //<< endl
      << " - mk_edge: " << making_edge //<< endl
      << " - after_nodes: " << after_nodes //<< endl
      << " - after_edges: " << after_edges //<< endl
      << " - next_char: " << next_char << endl;
  }
};

void
Network::fopen(const string filename)
{
  ifstream xmlread;
  xmlread.open(filename);
  readstate state;
  char next_char;
  int int_val;
  double double_val;
  
  
  while (xmlread.good())
    {
      if (state.read_int())
	{
	  xmlread >> int_val; // testa xmlread.good()?
	  cout << int_val; // för testning
	  state.step(int_val);
	}
      else if (state.read_double())
	{
	  xmlread >> double_val; // testa xmlread.good()?
	  cout << double_val; // för testning
	  state.step(double_val);
	}
      else
	{
	  xmlread.get(next_char);
	  if (!xmlread.good())
	    {
	      break;
	    }
	  cout << next_char; // för testning
	  state.step(next_char);
	}
    }

  //Fixa kommentarer i filen och andra taggar
  xmlread.close();
}
