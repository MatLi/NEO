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
#include <stack>

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


bool
Network::fwrite(const string filename)
{
  try
    {
      ofstream xmlwrite;
      xmlwrite.open(filename);
      unsigned int i=0; // Indexeras från 1
      
      xmlwrite << "<network number_of_nodes=\"" << nodes_.size() << "\">" << endl;
      xmlwrite << "  <nodes>" << endl;
      for (auto it : nodes_)
	{
	  (*it).change_id(++i);
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
  catch(...)
    {
      return false;
    }
  return true;
}

class readstate
{
public:

  readstate(Set<Edge*>* edges_,Set<Node*>* nodes_)
    :network_edges(edges_),network_nodes(nodes_) {}

private:

  // active data
  string word;
  string tagname;
  stack<string> tag;
  string label;
  char next_char = ' ';
  unsigned int int_val = 0;
  double double_val = 0;

  // flags
  bool in_tag = false;
  bool in_word = false;
  bool in_arg = false;
  bool closing_tag = false;
  bool close_tag = false;
  bool arg_expected = false;
  bool arg_ended = false;
  bool making_tagname = false;
  bool in_network = false;
  bool in_nodes = false;
  bool in_node = false;
  bool in_edges = false;
  bool in_edge = false;
  bool after_nodes = false;
  bool after_edges = false;
  
  // data of network
  int number_of_nodes = -1;
  vector<Node*> nodes;
  Set<Edge*>* network_edges;
  Set<Node*>* network_nodes;

  // data of nodes
  unsigned int node_id = 0; // Indexeras från 1, 0 = ej satt
  string node_name = "";
  double node_xpos = 0;
  double node_ypos = 0;
  double node_flow = 0;
  double node_price = 0; // // could be named node_node_price

  // data of edges
  double edge_flow = 0;
  double edge_reduced_cost = 0;
  double edge_cost = 0;
  double edge_max_flow = pow(10,380);
  double edge_min_flow = 0;
  unsigned int edge_from_node = 0; // Indexeras från 1, 0 = ej satt
  unsigned int edge_to_node = 0; // Indexeras från 1, 0 = ej satt

  // functions
  void make_tagname() // klar
  {
    if (!in_word)
      {
	throw network_error("empty tagname");
      }

    tagname = word;
    word = "";
    in_word = false;
    making_tagname = false;
    
    if (!close_tag) // om close_tag så kollas i end_tag()
      {
	if ((tagname == "network") and in_network)
	  {
	    throw network_error("malplaced network tag");
	  }
	else if ((tagname == "nodes") and
		 (in_nodes or after_nodes or !in_network))
	  {
	    throw network_error("malplaced nodes tag");
	  }
	else if ((tagname == "node") and
		 (in_node or !in_nodes))
	  {
	    throw network_error("malplaced node tag");
	  }
	else if ((tagname == "edges") and
		 (in_edges or after_edges or !after_nodes or !in_network))
	  {
	    throw network_error("malplaced edges tag");
	  }
	else if ((tagname == "edge") and
		 (in_edge or !in_edges))
	  {
	    throw network_error("malplaced node tag");
	  }
	else {} // Unknown tag, sätt flagga?
      }
  }

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
	make_tagname();
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
	throw network_error("malplaced opening bracket");
      }

    in_tag = true;
    making_tagname = true;
  }

  void
  slash() // klar
  {
    if (!in_tag or
	(in_word and !making_tagname) or
	arg_expected or
	in_arg or
	closing_tag)
      {
	throw network_error("malplaced slash");
      }

    closing_tag = true;
    if (in_word)
      {
	make_tagname();
      }
    else if (tagname == "")
      {
	close_tag = true;
      }
  }

  void
  alnum() // klar
  {
    if (arg_expected or
	(closing_tag and !making_tagname))
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
  equal() // klar
  {
    if (!in_word or making_tagname or in_arg)
      {
	throw network_error("malplaced equality sign");
      }
    
    in_word = false;
    label = word;
    word = "";
    arg_expected = true;
  }
  
  void
  quote() // klar
  {
    if (!arg_expected and !in_arg)
      {
	throw network_error("malplaced quotation sign");
      }
    
    if (arg_expected)
      {
	arg_expected = false;
	in_arg = true;
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

	if (tagname == "network")
	  {
	    if (label == "number_of_nodes")
	      {
		if (number_of_nodes >=0)
		  {
		    throw network_error("number of nodes can only be set once");
		  }
		
		number_of_nodes = int_val;
	      }
	    else
	      {
		throw network_error("label \""+label+"\" not allowed in network");
	      }
	  }
	else if (tagname == "node")
	  {
	    if (label == "id")
	      {
		if (int_val == 0)
		  {
		    throw network_error("id must be greater than zero");
		  }

		node_id = int_val;
	      }
	    else if (label == "name") {node_name = word;}
	    else if (label == "xpos") {node_xpos = double_val;}
	    else if (label == "ypos") {node_ypos = double_val;}
	    else if (label == "flow") {node_flow = double_val;}
	    else if (label == "node_price") {node_price = double_val;}
	    else
	      {
		throw network_error("label \""+label+"\" not allowed in node");
	      }
	  }
	else if (tagname == "edge")
	  {
	    if (label == "flow") {edge_flow = double_val;}
	    else if (label == "reduced_cost") {edge_reduced_cost = double_val;}
	    else if (label == "cost"){edge_cost = double_val;}
	    else if (label == "maxflow") {edge_max_flow = double_val;}
	    else if (label == "minflow") {edge_min_flow = double_val;}
	    else if (label == "from_node")
	      {
		if (int_val == 0)
		  {
		    throw network_error("id must be greater than zero");
		  }

		edge_from_node = int_val;
	      }
	    else if (label == "to_node")
	      {
		if (int_val == 0)
		  {
		    throw network_error("id must be greater than zero");
		  }

		edge_to_node = int_val;
	      }
	    else
	      {
		throw network_error("label \""+label+"\" not allowed in edge");
	      }
	  }
	else {} // Inget händer, främmande tag
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
	throw network_error("malplaced closing bracket");
      }

    if (making_tagname) {make_tagname();}

    if (closing_tag)
      {
	if (close_tag)
	  {
	    if (tagname != tag.top())
	      {
		throw network_error("unmatched tag");
	      }
	    
	    tag.pop();
	    close_tag = false;
	  }
	
	if (tagname == "network")
	  {
	    // kolla om number_of_nodes == 0, isf ok tomt nätverk, gör saker
	    // avsluta inläsningen
	  }
	else if (tagname == "nodes")
	  {
	    // kolla om alla noder är gjorda
	    in_nodes = false;
	    after_nodes = true;
	  }
	else if (tagname == "edges")
	  {
	    in_edges = false;
	    after_edges = true;
	  }
	else if (tagname == "node")
	  {
	    if (node_id == 0)
	      {
		throw network_error("id missing");
	      }
	    else if (nodes[node_id] != nullptr)
	      {
		throw network_error("duplicate id");
	      }
	    
	    Node* nd = new Node();
	    nd->change_id(node_id);
	    nd->change_name(node_name); // generera standardnamn om tom?
	    nd->change_position(Position(node_xpos,node_ypos));
	    nd->change_flow(node_flow);
	    nd->change_node_price(node_price);
	    nodes[node_id] = nd;
	    network_nodes->add_member(nd);

	    in_node = false;
	  }
	else if (tagname == "edge")
	  {
	    if (edge_from_node == 0 or edge_to_node == 0)
	      {
		throw network_error("connected node missing");
	      }
	    
	    Edge* ed = new Edge(nodes[edge_from_node],nodes[edge_to_node]);
	    ed->change_flow(edge_flow);
	    ed->change_reduced_cost(edge_reduced_cost);
	    ed->change_cost(edge_cost);
	    ed->change_maxflow(edge_max_flow);
	    ed->change_minflow(edge_min_flow);
	    network_edges->add_member(ed);

	    in_edge = false;
	  }
	
	closing_tag = false;
      }
    else
      {
	if (tagname == "network")
	  {
	    if (number_of_nodes < 0)
	      {
		throw network_error("number of nodes missing");
	      }
	    
	    in_network = true;
	    nodes.resize(number_of_nodes,nullptr);
	  }
	else if (tagname == "nodes")
	  {
	    in_nodes = true;
	  }
	else if (tagname == "edges")
	  {
	    in_edges = true;
	  }
	else if (tagname == "node")
	  {
	    in_node = true;
	  }
	else if (tagname == "edge")
	  {
	    in_edge = true;
	  }
	else {} // okänd tag
	
	tag.push(tagname);
      }
    in_tag = false;
    tagname = "";
  }

public:

  void
  step(const char next)
  {
    next_char = next;
    
    if (next_char == '<') {start_tag();}
    else if (in_tag)
      {
	if (isspace(next_char)) {space();}
	else if (next_char == '<') {start_tag();}
	else if (next_char == '/') {slash();}
	else if (isalnum(next_char) or next_char == '_') {alnum();}
	else if (next_char == '=') {equal();}
	else if (next_char == '\"') {quote();}
	else if (next_char == '>') {end_tag();}
	else {} // Unknown character
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
};

bool
Network::fopen(const string filename)
{
  // try
  //   {
      ifstream xmlread;
      xmlread.open(filename);
      readstate state(&edges_,&nodes_);
      char next_char;
      int int_val;
      double double_val;
      
      remove_all_edges();
      remove_all_nodes();
      while (xmlread.good())
	{
	  if (state.read_int())
	    {
	      xmlread >> int_val; // testa xmlread.good()?
	      state.step(int_val);
	    }
	  else if (state.read_double())
	    {
	      xmlread >> double_val; // testa xmlread.good()?
	      state.step(double_val);
	    }
	  else
	    {
	      xmlread.get(next_char);
	      if (!xmlread.good())
		{
		  break;
		}
	      state.step(next_char);
	    }
	}
      
      //Fixa kommentarer i filen och andra taggar/text utanför taggar
      xmlread.close();
    // }
  // catch(...)
  //   {
  //     return false;
  //   }
  return true;
}
