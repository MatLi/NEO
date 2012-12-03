#include "Node.h"
#include "Edge.h"
#include "Set.h"
#include "Path.h"
#include "Network.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
  // Testar Network

  Network net;
  net.add_node(new Node("Nod 1"));
  net.add_node(new Node("Nod 2"));
  net.add_node(new Node("Nod 3"));
  net.add_node(new Node("Nod 4"));
  net.add_node(new Node("Nod 5"));
  net.add_node(new Node("Nod 6"));

  cout << "Dessa noder finns i nätverket (med utkanter):" << endl;
  for (auto it : net.node_set())
    {
      cout << (*it).name() << ": ";
      for (auto it2 : (*it).out_edges())
	{
	  cout << &(*it2) << " ";
	}
      cout << endl;
    }

  cout << "Lägg till två kanter." << endl;
  for (auto it : net.node_set())
    {
      if ((*it).name() == "Nod 1")
	{
	  for (auto it2 : net.node_set())
	    {
	      if ((*it2).name() == "Nod 2")
		{
		  net.add_edge(new Edge(&(*it),&(*it2)));
		}
	      else if ((*it2).name() == "Nod 3")
		{
		  net.add_edge(new Edge(&(*it),&(*it2)));
		}
	    }
	}
    }

  cout << "Dessa noder finns i nätverket (med utkanter):" << endl;
  for (auto it : net.node_set())
    {
      cout << (*it).name() << ": ";
      for (auto it2 : (*it).out_edges())
	{
	  cout << &(*it2) << " ";
	}
      cout << endl;
    }

  cout << "Dessa bågar finns i nätverket:" << endl;
  for (auto it : net.edge_set())
    {
      cout << &(*it) << endl;
    }

  cout << "Ta bort Nod 1->Nod 2-kanten" << endl;
  for (auto it : net.edge_set())
    {
      if ((*it).to_node()->name() == "Nod 2")
	{
	  net.remove_edge(&(*it));
	}
    }
  cout << "Dessa noder finns i nätverket (med utkanter):" << endl;
  for (auto it : net.node_set())
    {
      cout << (*it).name() << ": ";
      for (auto it2 : (*it).out_edges())
	{
	  cout << &(*it2) << " ";
	}
      cout << endl;
    }
  cout << "Dessa bågar finns i nätverket:" << endl;
  for (auto it : net.edge_set())
    {
      cout << &(*it) << endl;
    }

  cout << "Ta bort alla kanter." << endl;
  net.remove_all_edges();
  cout << "Dessa noder finns i nätverket (med utkanter):" << endl;
  for (auto it : net.node_set())
    {
      cout << (*it).name() << ": ";
      for (auto it2 : (*it).out_edges())
	{
	  cout << &(*it2) << " ";
	}
      cout << endl;
    }
  cout << "Dessa bågar finns i nätverket:" << endl;
  for (auto it : net.edge_set())
    {
      cout << (*it).from_node()->name() << "->"
	   << (*it).to_node()->name() << endl;
    }

  net.remove_all_nodes();
  cout << "Dessa noder finns i nätverket:" << endl;
  for (auto it : net.node_set())
    {
      cout << (*it).name() << endl;
    }
  
  return 0;
}
