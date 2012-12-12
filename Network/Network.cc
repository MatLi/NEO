/* 
 * FILNAMN:          Network.cc
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Li, David, Linda och Jonas
 *
 * DATUM:            2012-11-21
 *
 * BESKRIVNING:
 * Network representerar ett helt n�tverk av noder och b�gar. 
 * L�sningarna till de olika problemen kommer att vara ett Network.    
*/

#include "Network.h"
#include <cmath>
#include <deque>
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

// Genererar en billigaste-tr�d-l�sning
// Utg�r fr�n att n�tverket �r "nollst�llt"
void
Network::cheapest_tree()
{
  //Tempor�ra variabler
  Node* working_node = nullptr;
  Set<Node*> Searched;
  Set<Node*> Unsearched(nodes_);
  Set<Edge*> Spanning_Edges;
  const unsigned int num_nodes = nodes_.size();

  if (nodes_.empty())
    {
      throw network_error("N�tverket saknar noder");
    }

  // Initialisera algoritmen.
  working_node = *Unsearched.begin();
  Searched.add_member(working_node);
  Unsearched.remove_member(working_node);

  //V�ljer f�rsta jobbnoden och justerar nodm�ngderna
  do
    {
      double min_cost = pow(10,380); //Maxv�rde f�r double i C++
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
	  throw network_error("Kan ej generera billigaste uppsp�nnande tr�d, det finns inte kanter till alla noder.");
	}
      else
	{
	  (*it).change_flow(1); // Tolkas som att kanten �r med i BUT.
	}
    }
  return;
}

// Genererar en billigaste-v�g-l�sning
// Anv�nder sig av mincostflow med specialvillkor,
// kanter i l�sningen markeras med fl�de 1.
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
      (*it).change_maxflow(pow(10,380));
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
 * Genererar minkostnadsfl�de med hj�lp av n�tverkssimplex.
 * St�ller upp Fas 1-problemet med en artificiell nod och artificiella b�gar. L�ser detta
 * problem med fas 2-funktionen f�r att f� ett till�tet fl�de. D�refter �terst�lls n�tverket
 * och fas 2-funktionen k�rs p� n�tverket med ett till�tet fl�de.
 * Kastar undantag om det saknas till�ten l�sning, samt om n�got blivit allvarligt fel (om cykel
 * inte existerar n�r den borde g�ra det).
 *********************************************************************************************/
void
Network::min_cost_flow()
{
  /****** 
   *Fas 1
   ******/
  Node* artificial = new Node("A");
  Set<Edge*> artificial_edges;

  // L�gg till den artificiella noden i n�tverket.
  add_node(artificial);

  // Se till att alla minfl�deskrav �r uppfyllda och spara ursprungliga
  // v�rden.
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

  // L�gg till kanter fr�n/till alla noder till/fr�n den artificiella noden.
  for (auto it : nodes_)
    {
      if ((*it).flow() < 0)
	{
	  // L�gg till b�gar fr�n alla k�llor till den artificiella
	  // noden.
	  Edge* new_edge = new Edge(&(*it), artificial);
	  add_edge(new_edge);
	  artificial_edges.add_member(new_edge);
	  new_edge->change_flow(abs((*it).flow()));
	}
      else if ((*it).flow() > 0)
	{
	  // L�gg till b�gar fr�n den artificiella noden till alla
	  // s�nkor.
	  Edge* new_edge = new Edge(artificial, &(*it));
	  add_edge(new_edge);
	  artificial_edges.add_member(new_edge);
	  new_edge->change_flow(abs((*it).flow()));
	}
      else if (&(*it) != artificial)
	{
	  // L�gg till b�gar fr�n den artificiella noden till alla andra
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
  

  // Best�m ursprungliga basb�gar och icke-basb�gar f�r fas 1.
  Set<Edge*> base_edges;
  Set<Edge*> non_base_edges;

  find_base_and_non_base_edges(base_edges, non_base_edges);
  
  // L�s Fas 1-problemet.
  double phase1_target_val = min_cost_flow_phase2(base_edges,
						  non_base_edges);

  // Om m�lfunktionsv�rdet inte �r 0, s� har vi ingen till�ten l�sning.
  if (phase1_target_val != 0)
    {
      throw network_error("Det finns ingen till�ten l�sning.");
    }

  // �terst�ll allt till det normala och k�r fas 2 p� den funna
  // till�tna l�sningen.

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
   * Allt �terst�llt. K�r Fas 2.
   *****************************/
  find_base_and_non_base_edges(base_edges, non_base_edges);

  min_cost_flow_phase2(base_edges,
		       non_base_edges);
  return;
}

/**********************************************************
 * find_base_and_non_base_edges(Set<Edge*>&, Set<Edge*>&)
 * Finner bas- och icke-basb�gar i ett till�tet fl�de.
 * F�ruts�tter till�tet fl�de.
 **********************************************************/
void
Network::find_base_and_non_base_edges(Set<Edge*>& base_edges,
				      Set<Edge*>& non_base_edges)
{
  base_edges.clear();
  non_base_edges.clear();
  // L�gg till de b�gar som m�ste vara basb�gar. S�tt alla andra till
  // icke-basb�gar.
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
  
  // Om det finns icke-kopplade noder, s� l�ggs s� m�nga
  // icke-basb�gar som beh�vs �ver i m�ngden av basb�gar.
  // Samtidigt bibeh�lls tr�dstrukturen.
  vector<Node*>::iterator itN = nodes_.begin(); //Inte s� snyggt, men f�r funka
  // tills vidare. Set<T> b�r uppdateras till att returnera Set<T>::iterator i
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
  // Best�m den utg�ende basb�gen i cykeln. x_node anv�nds h�r f�r
  // att avg�ra om vi har en fram�t- eller bak�tb�ge i cykeln.
  double theta = pow(10,380);
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
  // �ndra fl�dena i cykeln.
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
 * min_cost_flow_phase2(): L�ser fas 2-problem och f�ruts�tter att n�tverket har
 * ett till�tet fl�de och kr�ver att ursprungsfunktionen tillhandah�ller bas- och
 * icke-basb�gar i utg�ngsl�get.
 *******************************************************************************/
double
Network::min_cost_flow_phase2(Set<Edge*> base_edges,
			      Set<Edge*> non_base_edges)
{
  // S�tt alla noder till icke-kopplade.
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
  // Ber�kna de reducerade kostnaderna f�r icke-basb�gar.
  calculate_reduced_costs(non_base_edges);

  // Kontrollera avbrottskriterium och se till att de b�gar som inte
  // uppfyller kriterierna sparas i en m�ngd.
  Set<Edge*> unfulfilling_edges;
  bool optimal = optimal_mincostflow(unfulfilling_edges, non_base_edges);

  // Om fl�det �r optimalt, upph�r med rekursionen.
  if (optimal)
    {
      return flowcost();
    }

  // Fl�det �r icke-optimalt. Best�m en inkommande basb�ge.
  Edge* incoming_edge = find_incoming_edge(unfulfilling_edges);

  // Best�m s�kriktning och den cykel som uppkommer.
  Node* start_end_node = nullptr; // Noden som �r start- och slutnod i cykeln
  // (best�ms av find_cycle).
  deque<Edge*> cycle = find_cycle(base_edges, incoming_edge, start_end_node);

  // Cykeln f�r/kan inte vara tom...
  if (cycle.empty())
    {
      throw network_error("N�got allvarligt fel har intr�ffat: kan inte finna cykel.");
    }
  
  // Best�m utg�ende b�ge och st�rsta till�tna fl�des�ndring.
  Edge* outgoing_edge = nullptr; //Best�ms nedan.
  double theta = find_flow_change_outgoing_edge(cycle,
						start_end_node,
						outgoing_edge);

  // �ndra fl�det i cykeln.
  change_flow(cycle, start_end_node, theta);

  // Byt plats p� inkommande och utg�ende b�ge.
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

  // Om fl�det ligger p� undre gr�nsen ska fl�det �kas l�ngs den inkommande
  // b�gen.
  if (incoming_edge->reduced_cost() < 0)
    {
      start_end_node = incoming_edge->from_node();
      cycle = find_cycle_help(cycle,
			      base_edges,
			      start_end_node,
			      incoming_edge->to_node());
    }
  // Om fl�det ligger p� �vre gr�nsen ska fl�det minskas l�ngs den inkommande
  // b�gen (cykeln g�r "bakl�nges" l�ngs den inkommande b�gen).
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
 * Tar en ordnad m�ngd kanter (cycle) och ser till att returnera en
 * cykel av basb�gar, som b�rjar och slutar i search_node.
 * present_node �r den nod som f�r n�rvarande avs�ks.
 **************************************************************/
deque<Edge*>
Network::find_cycle_help(deque<Edge*> cycle,
			 Set<Edge*> base_edges,
			 Node* search_node,
			 Node* present_node)
{
  // Om vi hittat tillbaka s� har vi en cykel.
  if (present_node == search_node)
    {
      return cycle;
    }

  // Annars ser vi om vi kan hitta en cykel antingen p� nodens
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
  // Om vi inte hittat n�got s� returnerar vi en tom deque.
  return deque<Edge*>();
}

/********************************************************************
 * update_node_prices(Node*, Set<Edge*>)
 * Tar en f�rsta nod, med nodpris 0 och ber�knar alla �vriga noders
 * nodpriser utifr�n denna och tr�det av basb�gar.
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

// Genererar maxkostnadsfl�de
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

// Genererar maxfl�de
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
