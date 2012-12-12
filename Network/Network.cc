/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, David, Linda och Jonas
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt nätverk av noder och bågar. 
 * Lösningarna till de olika problemen kommer att vara ett Network.    
 */

#include "Network.h"
#include <cmath>
#include <deque>
#include <iostream>
#include <fstream>
#include <cctype>
#include <stack>
#include <string>

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

// Genererar en billigaste-träd-lösning
// Utgår från att nätverket är "nollställt"
void
Network::cheapest_tree()
{
  //Temporära variabler
  Node* working_node = nullptr;
  Set<Node*> Searched;
  Set<Node*> Unsearched(nodes_);
  Set<Edge*> Spanning_Edges;
  const unsigned int num_nodes = nodes_.size();

  if (nodes_.empty())
    {
      throw network_error("Nätverket saknar noder");
    }

  // Initialisera algoritmen.
  working_node = *Unsearched.begin();
  Searched.add_member(working_node);
  Unsearched.remove_member(working_node);

  //Väljer första jobbnoden och justerar nodmängderna
  do
    {
      double min_cost = pow(10,308); //Maxvärde för double i C++
      Edge* cheapest_current_edge = nullptr;
      for (auto it : edges_)
	{
	  if (Searched.exists((*it).from_node()) &&
	      Unsearched.exists((*it).to_node()))
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
      Unsearched.remove_member(cheapest_current_edge->to_node());
    } while(Spanning_Edges.size() < num_nodes - 1);

  for (auto it : Spanning_Edges)
    {
      if (&(*it) == nullptr)
	{
	  throw network_error("Kan ej generera billigaste uppspännande träd, det finns inte kanter till alla noder.");
	}
      else
	{
	  (*it).change_flow(1); // Tolkas som att kanten är med i BUT.
	}
    }
  return;
}

// Genererar en billigaste-väg-lösning
// Använder sig av mincostflow med specialvillkor,
// kanter i lösningen markeras med flöde 1.
void
Network::cheapest_path(Node* start_node, Node* end_node)
{
  for (auto it : nodes_)
    {
      (*it).backup_data();
      (*it).change_flow(0);
    }

  start_node->change_flow(-1);
  end_node->change_flow(1);

  for (auto it : edges_)
    {
      (*it).backup_data();
      (*it).change_minflow(0);
      (*it).change_maxflow(pow(10,308));
    }

  min_cost_flow();

  for (auto it : nodes_)
    {
      (*it).restore_data();
    }
  for (auto it : edges_)
    {
      (*it).restore_data();
    }
  return;
}

/*********************************************************************************************
 * Genererar minkostnadsflöde med hjälp av nätverkssimplex.
 * Ställer upp Fas 1-problemet med en artificiell nod och artificiella bågar. Löser detta
 * problem med fas 2-funktionen för att få ett tillåtet flöde. Därefter återställs nätverket
 * och fas 2-funktionen körs på nätverket med ett tillåtet flöde.
 * Kastar undantag om det saknas tillåten lösning, samt om något blivit allvarligt fel (om cykel
 * inte existerar när den borde göra det).
 *********************************************************************************************/
void
Network::min_cost_flow()
{
  /****** 
   *Fas 1
   ******/
  Node* artificial = new Node("A");
  Set<Edge*> artificial_edges;

  // Lägg till den artificiella noden i nätverket.
  add_node(artificial);

  // Se till att alla minflödeskrav är uppfyllda och spara ursprungliga
  // värden.
  for (auto it : edges_)
    {
      (*it).backup_data();
      if ((*it).minflow() > 0)
	{
	  (*it).from_node()->change_flow((*it).from_node()->flow() +
					 (*it).minflow());
	  (*it).to_node()->change_flow((*it).to_node()->flow() -
				       (*it).minflow());
	  (*it).change_maxflow((*it).maxflow() - (*it).minflow());
	  (*it).change_minflow(0);
	}
    }

  // Lägg till kanter från/till alla noder till/från den artificiella noden.
  for (auto it : nodes_)
    {
      if ((*it).flow() < 0)
	{
	  // Lägg till bågar från alla källor till den artificiella
	  // noden.
	  Edge* new_edge = new Edge(&(*it), artificial);
	  add_edge(new_edge);
	  artificial_edges.add_member(new_edge);
	  new_edge->change_flow(abs((*it).flow()));
	}
      else if ((*it).flow() > 0)
	{
	  // Lägg till bågar från den artificiella noden till alla
	  // sänkor.
	  Edge* new_edge = new Edge(artificial, &(*it));
	  add_edge(new_edge);
	  artificial_edges.add_member(new_edge);
	  new_edge->change_flow(abs((*it).flow()));
	}
      else if (&(*it) != artificial)
	{
	  // Lägg till bågar från den artificiella noden till alla andra
	  // mellannoder.
	  Edge* new_edge = new Edge(artificial, &(*it));
	  add_edge(new_edge);
	  artificial_edges.add_member(new_edge);
	}
    }
  
  for (auto it : edges_)
    {
      (*it).change_cost(0);
    }
  for (auto it : artificial_edges)
    {
      (*it).change_cost(1);
    }
  

  // Bestäm ursprungliga basbågar och icke-basbågar för fas 1.
  Set<Edge*> base_edges;
  Set<Edge*> non_base_edges;

  find_base_and_non_base_edges(base_edges, non_base_edges);
  
  // Lös Fas 1-problemet.
  double phase1_target_val = min_cost_flow_phase2(base_edges,
						  non_base_edges);

  // Om målfunktionsvärdet inte är 0, så har vi ingen tillåten lösning.
  if (phase1_target_val != 0)
    {
      throw network_error("Det finns ingen tillåten lösning.");
    }

  // Återställ allt till det normala och kör fas 2 på den funna
  // tillåtna lösningen.

  for (auto it : artificial_edges)
    {
      remove_edge(&(*it));
    }
  artificial_edges.clear();
  base_edges.clear();
  non_base_edges.clear();
  remove_node(artificial);

  for (auto it : edges_)
    {
      (*it).restore_data();
      if ((*it).minflow() > 0)
	{
	  (*it).from_node()->change_flow((*it).from_node()->flow() +
					 (*it).minflow());
	  (*it).to_node()->change_flow((*it).to_node()->flow() -
				       (*it).minflow());
	  (*it).change_flow((*it).flow() + (*it).minflow());
	}
    }

  /*****************************
   * Allt återställt. Kör Fas 2.
   *****************************/
  find_base_and_non_base_edges(base_edges, non_base_edges);

  min_cost_flow_phase2(base_edges,
		       non_base_edges);
  return;
}

/**********************************************************
 * find_base_and_non_base_edges(Set<Edge*>&, Set<Edge*>&)
 * Finner bas- och icke-basbågar i ett tillåtet flöde.
 * Förutsätter tillåtet flöde.
 **********************************************************/
void
Network::find_base_and_non_base_edges(Set<Edge*>& base_edges,
				      Set<Edge*>& non_base_edges)
{
  base_edges.clear();
  non_base_edges.clear();
  // Lägg till de bågar som måste vara basbågar. Sätt alla andra till
  // icke-basbågar.
  for (auto it : edges_)
    {
      if ((*it).flow() > (*it).minflow() && (*it).flow() < (*it).maxflow())
	{
	  base_edges.add_member(&(*it));
	}
      else
	{
	  non_base_edges.add_member(&(*it));
	}
    }
  
  for (auto it : nodes_)
    {
      (*it).set_connected(false);
    }
 
  for (auto it : base_edges)
    {
      (*it).from_node()->set_connected(true);
      (*it).to_node()->set_connected(true);
    }
  
  // Om det finns icke-kopplade noder, så läggs så många
  // icke-basbågar som behövs över i mängden av basbågar.
  // Samtidigt bibehålls trädstrukturen.
  vector<Node*>::iterator itN = nodes_.begin(); //Inte så snyggt, men får funka
  // tills vidare. Set<T> bör uppdateras till att returnera Set<T>::iterator i
  // kommande versioner.
  while (base_edges.size() < nodes_.size() - 1)
    {
      if (!(*itN)->connected())
	{
	  for (auto it : (*itN)->all_edges())
	    {
	      if ((*it).to_node()->connected() ||
		  (*it).from_node()->connected())
		{
		  base_edges.add_member(&(*it));
		  non_base_edges.remove_member(&(*it));
		  (*itN)->set_connected(true);
		  break;
		}
	    }
	}
      
      if (itN == nodes_.end())
	{
	  itN = nodes_.begin();
	}
      else
	{
	  itN++;
	}
    }

  return;
}

void
Network::calculate_reduced_costs(Set<Edge*> non_base_edges)
{
  for (auto it : non_base_edges)
    {
      (*it).change_reduced_cost((*it).cost() +
				(*it).from_node()->node_price() -
				(*it).to_node()->node_price());
    }
}

bool
Network::optimal_mincostflow(Set<Edge*>& unfulfilling_edges,
			     Set<Edge*> non_base_edges)
{
  bool optimal = true;
  for (auto it : non_base_edges)
    {
      if ((*it).reduced_cost() == 0 &&
	  (*it).flow() <= (*it).maxflow() &&
	  (*it).flow() >= (*it).minflow())
	{
	  optimal = optimal && true;
	}
      else if ((*it).reduced_cost() < 0 &&
	       (*it).flow() == (*it).maxflow())
	{
	  optimal = optimal && true;
	}
      else if ((*it).reduced_cost() > 0 &&
	       (*it).flow() == (*it).minflow())
	{
	  optimal = optimal && true;
	}
      else
	{
	  unfulfilling_edges.add_member(&(*it));
	  optimal = false;
	}
    }

  return optimal;
}

Edge* 
Network::find_incoming_edge(Set<Edge*> unfulfilling_edges)
{
  double max_reduced_cost = 0;
  Edge* incoming_edge = nullptr;
  for (auto it : unfulfilling_edges)
    {
      if (abs((*it).reduced_cost()) > max_reduced_cost)
	{
	  incoming_edge = &(*it);
	  max_reduced_cost = abs((*it).reduced_cost());
	}
    }

  return incoming_edge;
}

double
Network::find_flow_change_outgoing_edge(deque<Edge*> cycle,
					Node* x_node,
					Edge*& outgoing_edge)
{
  // Bestäm den utgående basbågen i cykeln. x_node används här för
  // att avgöra om vi har en framåt- eller bakåtbåge i cykeln.
  double theta = pow(10,308);
  for (auto it : cycle)
    {
      if ((*it).from_node() == x_node)
	{
	  if ((*it).maxflow() - (*it).flow() < theta)
	    {
	      theta = (*it).maxflow() - (*it).flow();
	      outgoing_edge = &(*it);
	    }
	  x_node = (*it).to_node();
	}
      else if ((*it).to_node() == x_node)
	{
	  if ((*it).flow() - (*it).minflow() < theta)
	    {
	      theta = (*it).flow() - (*it).minflow();
	      outgoing_edge = &(*it);
	    }
	  x_node = (*it).from_node();
	}
    }
  return theta;
}

void
Network::change_flow(deque<Edge*> cycle,
		     Node* x_node,
		     double theta)
{
  // Ändra flödena i cykeln.
  for (auto it : cycle)
    {
      if ((*it).from_node() == x_node)
	{
	  (*it).change_flow((*it).flow() + theta);
	  x_node = (*it).to_node();
	}
      else if ((*it).to_node() == x_node)
	{
	  (*it).change_flow((*it).flow() - theta);
	  x_node = (*it).from_node();
	}
    }
}

double
Network::flowcost()
{
  double target_value = 0;
  for (auto it : edges_)
    {
      target_value += (*it).flow() * (*it).cost();
    }
  return target_value;
}


/*******************************************************************************
 * min_cost_flow_phase2(): Löser fas 2-problem och förutsätter att nätverket har
 * ett tillåtet flöde och kräver att ursprungsfunktionen tillhandahåller bas- och
 * icke-basbågar i utgångsläget.
 *******************************************************************************/
double
Network::min_cost_flow_phase2(Set<Edge*> base_edges,
			      Set<Edge*> non_base_edges)
{
  // Sätt alla noder till icke-kopplade.
  for (auto it : nodes_)
    {
      (*it).set_connected(false);
    }
  // Uppdatera alla nodpriser. start_node ska ha nodpris 0.
  for (auto it : nodes_)
    {
      (*it).change_node_price(0);
    }
  update_node_prices(*nodes_.begin(), base_edges);
  // Beräkna de reducerade kostnaderna för icke-basbågar.
  calculate_reduced_costs(non_base_edges);

  // Kontrollera avbrottskriterium och se till att de bågar som inte
  // uppfyller kriterierna sparas i en mängd.
  Set<Edge*> unfulfilling_edges;
  bool optimal = optimal_mincostflow(unfulfilling_edges, non_base_edges);

  // Om flödet är optimalt, upphör med rekursionen.
  if (optimal)
    {
      return flowcost();
    }

  // Flödet är icke-optimalt. Bestäm en inkommande basbåge.
  Edge* incoming_edge = find_incoming_edge(unfulfilling_edges);

  // Bestäm sökriktning och den cykel som uppkommer.
  Node* start_end_node = nullptr; // Noden som är start- och slutnod i cykeln
  // (bestäms av find_cycle).
  deque<Edge*> cycle = find_cycle(base_edges, incoming_edge, start_end_node);

  // Cykeln får/kan inte vara tom...
  if (cycle.empty())
    {
      throw network_error("Något allvarligt fel har inträffat: kan inte finna cykel.");
    }
  
  // Bestäm utgående båge och största tillåtna flödesändring.
  Edge* outgoing_edge = nullptr; //Bestäms nedan.
  double theta = find_flow_change_outgoing_edge(cycle,
						start_end_node,
						outgoing_edge);

  // Ändra flödet i cykeln.
  change_flow(cycle, start_end_node, theta);

  // Byt plats på inkommande och utgående båge.
  non_base_edges.remove_member(incoming_edge);
  base_edges.add_member(incoming_edge);
  base_edges.remove_member(outgoing_edge);
  non_base_edges.add_member(outgoing_edge);
  
  // Rekursivt steg.
  return min_cost_flow_phase2(base_edges, non_base_edges);
}

// exists(deque<Edge*>, Edge*): Sant omm e finns i dq
bool
Network::exists(deque<Edge*> dq,
		Edge* e)
{
  bool retval = false;
  for (auto it : dq)
    {
      if (&(*it) == e)
	retval = true;
    }
  return retval;
}

deque<Edge*>
Network::find_cycle(Set<Edge*> base_edges,
		    Edge* incoming_edge,
		    Node*& start_end_node)
{
  deque<Edge*> cycle;
  cycle.push_back(incoming_edge);

  // Om flödet ligger på undre gränsen ska flödet ökas längs den inkommande
  // bågen.
  if (incoming_edge->reduced_cost() < 0)
    {
      start_end_node = incoming_edge->from_node();
      cycle = find_cycle_help(cycle,
			      base_edges,
			      start_end_node,
			      incoming_edge->to_node());
    }
  // Om flödet ligger på övre gränsen ska flödet minskas längs den inkommande
  // bågen (cykeln går "baklänges" längs den inkommande bågen).
  else if (incoming_edge->reduced_cost() > 0)
    {
      start_end_node = incoming_edge->to_node();
      cycle = find_cycle_help(cycle,
			      base_edges,
			      start_end_node,
			      incoming_edge->from_node());
    }
  return cycle;
}

/**************************************************************
 * find_cycle_help(deque<Edge*>, Set<Edge*>, Node*, Node*)
 * Tar en ordnad mängd kanter (cycle) och ser till att returnera en
 * cykel av basbågar, som börjar och slutar i search_node.
 * present_node är den nod som för närvarande avsöks.
 **************************************************************/
deque<Edge*>
Network::find_cycle_help(deque<Edge*> cycle,
			 Set<Edge*> base_edges,
			 Node* search_node,
			 Node* present_node)
{
  // Om vi hittat tillbaka så har vi en cykel.
  if (present_node == search_node)
    {
      return cycle;
    }

  // Annars ser vi om vi kan hitta en cykel antingen på nodens
  // utkanter eller inkanter.
  for (auto it : present_node->out_edges())
    {
      deque<Edge*> retval = cycle;
      if (base_edges.exists(&(*it)) &&
	  !exists(cycle, &(*it)))
	{
	  retval.push_back(&(*it));
	  retval = find_cycle_help(retval,
				   base_edges,
				   search_node,
				   (*it).to_node());
	  if (!retval.empty())
	    {
	      return retval;
	    }
	}
    }
  for (auto it : present_node->in_edges())
    {
      deque<Edge*> retval = cycle;
      if (base_edges.exists(&(*it)) &&
	  !exists(cycle, &(*it)))
	{
	  retval.push_back(&(*it));
	  retval = find_cycle_help(retval,
				   base_edges,
				   search_node,
				   (*it).from_node());
	  if (!retval.empty())
	    {
	      return retval;
	    }
	}
    }
  // Om vi inte hittat något så returnerar vi en tom deque.
  return deque<Edge*>();
}

/********************************************************************
 * update_node_prices(Node*, Set<Edge*>)
 * Tar en första nod, med nodpris 0 och beräknar alla övriga noders
 * nodpriser utifrån denna och trädet av basbågar.
 ********************************************************************/
void
Network::update_node_prices(Node* active_node, Set<Edge*> base_edges)
{
  active_node->set_connected(true);
  for (auto it : active_node->out_edges())
    {
      if (base_edges.exists(&(*it)) &&
	  !(*it).to_node()->connected())
	{
	  (*it).to_node()->change_node_price(active_node->node_price() + (*it).cost());
	  update_node_prices((*it).to_node(),
			     base_edges);
	}
    }
  for (auto it : active_node->in_edges())
    {
      if (base_edges.exists(&(*it)) &&
	  !(*it).from_node()->connected())
	{
	  (*it).from_node()->change_node_price(active_node->node_price() - (*it).cost());
	  update_node_prices((*it).from_node(),
			     base_edges);
	}
    }
  return;
}

// Genererar maxkostnadsflöde
void
Network::max_cost_flow()
{
  for (auto it : edges_)
    {
      (*it).backup_data();
      (*it).change_cost(-abs((*it).cost()));
    }

  min_cost_flow();

  for (auto it : edges_)
    {
      (*it).restore_data();
    }
}

// Genererar maxflöde
void
Network::max_flow()
{
  for (auto it : edges_)
    {
      (*it).backup_data();
      (*it).change_cost(0);
    }
  Node* super_source = new Node("SSo");
  Node* super_sink = new Node("SSi");
  Set<Edge*> added_edges;
  super_source->change_flow(-1);
  super_sink->change_flow(1);
  for (auto it : nodes_)
    {
      (*it).backup_data();
      if ((*it).flow() < 0)
	{
	  Edge* so_edge = new Edge(super_source, &(*it));
	  added_edges.add_member(so_edge);
	  add_edge(so_edge);
	}
      if ((*it).flow() > 0)
	{
	  Edge* si_edge = new Edge(&(*it), super_sink);
	  added_edges.add_member(si_edge);
	  add_edge(si_edge);
	}
      (*it).change_flow(0);
    }
  add_node(super_source);
  add_node(super_sink);

  Edge* back_edge = new Edge(super_sink, super_source);
  back_edge->change_cost(-1);

  added_edges.add_member(back_edge);
  add_edge(back_edge);

  min_cost_flow();

  for (auto it : added_edges)
    {
      if ((*it).flow() > 0 &&
	  (*it).from_node() == super_source)
	{
	  (*it).to_node()->change_flow(-(*it).flow());
	}
      else if ((*it).flow() > 0 &&
	       (*it).to_node() == super_sink)
	{
	  (*it).from_node()->change_flow((*it).flow());
	}
      remove_edge(&(*it));
    }
  added_edges.clear();
  remove_node(super_source);
  remove_node(super_sink);

  for (auto it : edges_)
    {
      (*it).restore_data();
    }

  return;
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
      xmlwrite.precision(17);
      unsigned int i=0; // Indexeras från 1
      
      xmlwrite << "<network number_of_nodes=\"" << nodes_.size() << "\">" << endl;
      xmlwrite << "  <nodes>" << endl;
      for (auto it : nodes_)
	{
	  (*it).change_id(++i);
	  xmlwrite << "    <node "
		   << "id=\"" << (*it).id() << "\" "
		   << "name=\"" << (*it).name() << "\" " // behöver kanske encodas
		   << "xpos=\"" << (*it).xpos() << "\" "
		   << "ypos=\"" << (*it).ypos() << "\" "
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
  double edge_max_flow = pow(10,308);
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
	else {} // Unknown tag, sätta flagga behövs ej
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
    else {}
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
	    else if (nodes[node_id-1] != nullptr)
	      {
		throw network_error("duplicate id");
	      }
	    
	    Node* nd = new Node();
	    nd->change_id(node_id);
	    nd->change_name(node_name); // generera standardnamn om tom?
	    nd->change_xpos(node_xpos);
	    nd->change_ypos(node_ypos);
	    nd->change_flow(node_flow);
	    nd->change_node_price(node_price);
	    nodes[node_id-1] = nd;
	    network_nodes->add_member(nd);

	    in_node = false;
	    node_id = 0;
	    node_name = "";
	    node_xpos = 0;
	    node_ypos = 0;
	    node_flow = 0;
	    node_price = 0;
	  }
	else if (tagname == "edge")
	  {
	    if (edge_from_node == 0 or edge_to_node == 0)
	      {
		throw network_error("connected node missing");
	      }
	    
	    Edge* ed = new Edge(nodes[edge_from_node-1],nodes[edge_to_node-1]);
	    ed->change_flow(edge_flow);
	    ed->change_reduced_cost(edge_reduced_cost);
	    ed->change_cost(edge_cost);
	    ed->change_maxflow(edge_max_flow);
	    ed->change_minflow(edge_min_flow);
	    network_edges->add_member(ed);

	    in_edge = false;
	    edge_from_node = 0;
	    edge_to_node = 0;
	    edge_flow = 0;
	    edge_reduced_cost = 0;
	    edge_cost = 0;
	    edge_max_flow = pow(10,308);
	    edge_min_flow = 0;
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
  try
    {
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
      
      //Fixa kommentarer i filen
      xmlread.close();
    }
  catch(...)
    {
      return false;
    }
  return true;
}
