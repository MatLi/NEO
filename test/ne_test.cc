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
  Node* n1 = new Node("Nod 1");
  Node* n2 = new Node("Nod 2");
  Node* n3 = new Node("Nod 3");
  Node* n4 = new Node("Nod 4");
  Node* n5 = new Node("Nod 5");
  net.add_node(n1);
  net.add_node(n2);
  net.add_node(n3);
  net.add_node(n4);
  net.add_node(n5);

  Edge* e1 = new Edge(n1,n2);
  Edge* e2 = new Edge(n2,n1);
  Edge* e3 = new Edge(n1,n3);
  Edge* e4 = new Edge(n3,n1);
  Edge* e5 = new Edge(n1,n4);
  Edge* e6 = new Edge(n4,n1);
  Edge* e7 = new Edge(n2,n3);
  Edge* e8 = new Edge(n3,n2);
  Edge* e9 = new Edge(n2,n5);
  Edge* e10 = new Edge(n5,n2);
  Edge* e11 = new Edge(n3,n5);
  Edge* e12 = new Edge(n5,n3);
  Edge* e13 = new Edge(n3,n4);
  Edge* e14 = new Edge(n4,n3);
  Edge* e15 = new Edge(n4,n5);
  Edge* e16 = new Edge(n5,n4);

   e1->change_cost(6);
   e2->change_cost(6);
  
   e3->change_cost(0.8);
   e4->change_cost(5.12);

   e5->change_cost(6.5);
   e6->change_cost(6);

   e7->change_cost(2);
   e8->change_cost(2);
  
   e9->change_cost(4);
   e10->change_cost(4);

   e11->change_cost(3);
   e12->change_cost(3);

   e13->change_cost(3);
   e14->change_cost(3);
  
   e15->change_cost(1);
   e16->change_cost(1);

  net.add_edge(e1);
  net.add_edge(e2);
  net.add_edge(e3);
  net.add_edge(e4);
  net.add_edge(e5);
  net.add_edge(e6);
  net.add_edge(e7);
  net.add_edge(e8);
  net.add_edge(e9);
  net.add_edge(e10);
  net.add_edge(e11);
  net.add_edge(e12);
  net.add_edge(e13);
  net.add_edge(e14);
  net.add_edge(e15);
  net.add_edge(e16);

  // net.cheapest_tree();

  // cout << "Bågar i trädet." << endl;
  // for (auto it : net.edge_set())
  //   {
  //     if ((*it).flow() == 1)
  // 	{
  // 	  cout << (*it).from_node()->name() << "->"
  // 	       << (*it).to_node()->name() << endl;
  // 	}
  //   }

  net.fwrite("testfil.txt");
  net.fopen("testfil.txt");
  
  return 0;
}
