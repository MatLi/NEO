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

  // Network net;
  // Node* n1 = new Node("Nod 1");
  // Node* n2 = new Node("Nod 2");
  // Node* n3 = new Node("Nod 3");
  // Node* n4 = new Node("Nod 4");
  // Node* n5 = new Node("Nod 5");
  // net.add_node(n1);
  // net.add_node(n2);
  // net.add_node(n3);
  // net.add_node(n4);
  // net.add_node(n5);

  // Edge* e1 = new Edge(n1,n2);
  // Edge* e2 = new Edge(n2,n1);
  // Edge* e3 = new Edge(n1,n3);
  // Edge* e4 = new Edge(n3,n1);
  // Edge* e5 = new Edge(n1,n4);
  // Edge* e6 = new Edge(n4,n1);
  // Edge* e7 = new Edge(n2,n3);
  // Edge* e8 = new Edge(n3,n2);
  // Edge* e9 = new Edge(n2,n5);
  // Edge* e10 = new Edge(n5,n2);
  // Edge* e11 = new Edge(n3,n5);
  // Edge* e12 = new Edge(n5,n3);
  // Edge* e13 = new Edge(n3,n4);
  // Edge* e14 = new Edge(n4,n3);
  // Edge* e15 = new Edge(n4,n5);
  // Edge* e16 = new Edge(n5,n4);

  // e1->change_cost(6);
  // e2->change_cost(6);
  
  // e3->change_cost(5);
  // e4->change_cost(5);

  // e5->change_cost(6);
  // e6->change_cost(6);

  // e7->change_cost(2);
  // e8->change_cost(2);
  
  // e9->change_cost(4);
  // e10->change_cost(4);

  // e11->change_cost(3);
  // e12->change_cost(3);

  // e13->change_cost(3);
  // e14->change_cost(3);
  
  // e15->change_cost(1);
  // e16->change_cost(1);

  // net.add_edge(e1);
  // net.add_edge(e2);
  // net.add_edge(e3);
  // net.add_edge(e4);
  // net.add_edge(e5);
  // net.add_edge(e6);
  // net.add_edge(e7);
  // net.add_edge(e8);
  // net.add_edge(e9);
  // net.add_edge(e10);
  // net.add_edge(e11);
  // net.add_edge(e12);
  // net.add_edge(e13);
  // net.add_edge(e14);
  // net.add_edge(e15);
  // net.add_edge(e16);

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

  //  net.fwrite("testfil.txt");
  //  net.fopen("testfil.txt");
  Network net2;
  Node* W = new Node();
  Node* N = new Node();
  Node* S = new Node();
  Node* E = new Node();
  W->change_flow(-2);
  E->change_flow(2);
  net2.add_node(W);
  net2.add_node(N);
  net2.add_node(S);
  net2.add_node(E);
  Edge* WN = new Edge(W,N);
  Edge* NE = new Edge(N,E);
  Edge* WS = new Edge(W,S);
  Edge* SE = new Edge(S,E);
  net2.add_edge(WN);
  net2.add_edge(NE);
  net2.add_edge(WS);
  net2.add_edge(SE);
  WN->change_cost(3);
  NE->change_cost(1);
  WS->change_cost(1);
  SE->change_cost(2);
  
  cout << "W: " << W << endl;
  cout << "N: " << N << endl;
  cout << "S: " << S << endl;
  cout << "E: " << E << endl;
  net2.min_cost_flow();
  cout << net2.flowcost() << endl;
  cout << "Flow: " << endl;
  cout << "WN: " << WN->flow() << endl;
  cout << "NE: " << NE->flow() << endl;
  cout << "WS: " << WS->flow() << endl;
  cout << "SE: " << SE->flow() << endl;
  cout << "Edge set size: " << net2.edge_set().size() << endl;

  Network net3;
  Node* no1 = new Node("1");
  Node* no2 = new Node("2");
  Node* no3 = new Node("3");
  Node* no4 = new Node("4");
  Node* no5 = new Node("5");
  Node* no6 = new Node("6");
  net3.add_node(no1);
  net3.add_node(no2);
  net3.add_node(no3);
  net3.add_node(no4);
  net3.add_node(no5);
  net3.add_node(no6);
  no1->change_flow(-9);
  no5->change_flow(3);
  no6->change_flow(6);
  Edge* e12 = new Edge(no1,no2);
  e12->change_cost(4);
  e12->change_minflow(4);
  e12->change_maxflow(8);
  Edge* e13 = new Edge(no1,no3);
  e13->change_cost(3);
  e13->change_minflow(0);
  e13->change_maxflow(5);
  Edge* e23 = new Edge(no2,no3);
  e23->change_cost(2);
  e23->change_minflow(0);
  e23->change_maxflow(3);
  Edge* e24 = new Edge(no2,no4);
  e24->change_cost(6);
  e24->change_minflow(0);
  e24->change_maxflow(4);
  Edge* e25 = new Edge(no2,no5);
  e25->change_cost(4);
  e25->change_minflow(0);
  e25->change_maxflow(3);
  Edge* e34 = new Edge(no3,no4);
  e34->change_cost(4);
  e34->change_minflow(0);
  e34->change_maxflow(4);
  Edge* e36 = new Edge(no3,no6);
  e36->change_cost(6);
  e36->change_minflow(0);
  e36->change_maxflow(3);
  Edge* e45 = new Edge(no4,no5);
  e45->change_cost(4);
  e45->change_minflow(0);
  e45->change_maxflow(4);
  Edge* e46 = new Edge(no4,no6);
  e46->change_cost(4);
  e46->change_minflow(1);
  e46->change_maxflow(2);
  Edge* e56 = new Edge(no5,no6);
  e56->change_cost(3);
  e56->change_minflow(0);
  e56->change_maxflow(5);

  net3.add_edge(e12);
  net3.add_edge(e13);
  net3.add_edge(e23);
  net3.add_edge(e24);
  net3.add_edge(e25);
  net3.add_edge(e34);
  net3.add_edge(e36);
  net3.add_edge(e45);
  net3.add_edge(e46);
  net3.add_edge(e56);

  cout << "Solving net3 mincostflow..." << endl;
  net3.min_cost_flow();
  cout << "Minimum cost: " << net3.flowcost() << endl;
  cout << "Edge set size: " << net3.edge_set().size() << endl;

  cout << "Edge (flow, cost):" << endl;
  for (auto it : net3.edge_set())
    {
      cout << (*it).from_node()->name() << "->"
	   << (*it).to_node()->name() << " ("
	   << (*it).flow() << ", " << (*it).cost() << ")" << endl;
    }

  Network net4;
  Node* NS = new Node("Siljeåsen");
  Node* NN = new Node("Norrstig");
  Node* NM = new Node("Mellansel");
  Node* NL = new Node("Lunden");
  Node* NT = new Node("Tunada");
  Node* NG = new Node("Graninge");
  Node* NH = new Node("Holmsund");
  net4.add_node(NS);
  net4.add_node(NN);
  net4.add_node(NM);
  net4.add_node(NL);
  net4.add_node(NT);
  net4.add_node(NG);
  net4.add_node(NH);

  NS->change_flow(-2400);
  NG->change_flow(-1800);
  NL->change_flow(-1400);
  NH->change_flow(3500);
  NT->change_flow(2100);

  net4.fwrite("testfil.txt");
  net4.fopen("testfil.txt");

  
  Edge* ESM = new Edge(NS,NM);
  Edge* ESN = new Edge(NS,NN);
  Edge* ESH = new Edge(NS,NH);
  Edge* ENH = new Edge(NN,NH);
  Edge* ENM = new Edge(NN,NM);
  Edge* EMN = new Edge(NM,NN);
  Edge* EMT = new Edge(NM,NT);
  Edge* EGM = new Edge(NG,NM);
  Edge* EGN = new Edge(NG,NN);
  Edge* EGH = new Edge(NG,NH);
  Edge* EGT = new Edge(NG,NT);
  Edge* ELM = new Edge(NL,NM);
  Edge* ELT = new Edge(NL,NT);

  net4.add_edge(ESM);
  net4.add_edge(ESN);
  net4.add_edge(ESH);
  net4.add_edge(ENH);
  net4.add_edge(ENM);
  net4.add_edge(EMN);
  net4.add_edge(EMT);
  net4.add_edge(EGM);
  net4.add_edge(EGN);
  net4.add_edge(EGH);
  net4.add_edge(EGT);
  net4.add_edge(ELM);
  net4.add_edge(ELT);

  ESN->change_cost(20);
  ESN->change_maxflow(900);
  ESM->change_cost(26);
  ESM->change_maxflow(1000);
  ESH->change_cost(45);
  ESH->change_maxflow(1100);
  EGN->change_cost(8);
  EGN->change_maxflow(700);
  EGM->change_cost(14);
  EGM->change_maxflow(900);
  EGH->change_cost(37);
  EGH->change_maxflow(600);
  EGT->change_cost(22);
  EGT->change_maxflow(600);
  ELM->change_cost(32);
  ELM->change_maxflow(600);
  ELT->change_cost(23);
  ELT->change_maxflow(1000);
  ENH->change_cost(11);
  ENH->change_maxflow(1800);
  ENM->change_cost(9);
  ENM->change_maxflow(1800);
  EMN->change_cost(9);
  EMN->change_maxflow(1800);
  EMT->change_cost(9);
  EMT->change_maxflow(1800);

  cout << "Solving net4 mincostflow..." << endl;
  net4.min_cost_flow();
  cout << "Minimum cost: " << net4.flowcost() << endl;
  cout << "Edge set size: " << net4.edge_set().size() << endl;

  cout << "Edge (flow, cost):" << endl;
  for (auto it : net4.edge_set())
    {
      cout << (*it).from_node()->name() << "->"
	   << (*it).to_node()->name() << " ("
	   << (*it).flow() << ", " << (*it).cost() << ")" << endl;
    }
  cout << "Solving net4 cheapest_path from " << NN->name() << " to "
       << NT->name() << "." << endl;
  net4.reset_network();
  net4.cheapest_path(NN,NT);
  cout << "Edges in cheapest path: " << endl;
  for (auto it : net4.edge_set())
    {
      if ((*it).flow() > 0)
	{
	  cout << (*it).from_node()->name() << "->"
	       << (*it).to_node()->name() << endl;
	}
    }
  cout << "Solving net4 maxcostflow..." << endl;
  net4.reset_network();
  net4.max_cost_flow();
  cout << "Maximum cost: " << net4.flowcost() << endl;
  cout << "Edge set size: " << net4.edge_set().size() << endl;

  cout << "Edge (flow, cost):" << endl;
  for (auto it : net4.edge_set())
    {
      cout << (*it).from_node()->name() << "->"
	   << (*it).to_node()->name() << " ("
	   << (*it).flow() << ", " << (*it).cost() << ")" << endl;
    }

  Network net5;
  Node* Ns = new Node("s");
  Node* N1 = new Node("1");
  Node* N2 = new Node("2");
  Node* N3 = new Node("3");
  Node* N4 = new Node("4");
  Node* N5 = new Node("5");
  Node* N6 = new Node("6");
  Node* N7 = new Node("7");
  Node* Nt = new Node("t");
  net5.add_node(Ns);
  Ns->change_flow(-1);
  net5.add_node(N1);
  net5.add_node(N2);
  net5.add_node(N3);
  net5.add_node(N4);
  net5.add_node(N5);
  net5.add_node(N6);
  net5.add_node(N7);
  net5.add_node(Nt);
  Nt->change_flow(1);

  Edge* Es1 = new Edge(Ns,N1);
  Edge* Es2 = new Edge(Ns,N2);
  Edge* E12 = new Edge(N1,N2);
  Edge* E21 = new Edge(N2,N1);
  Edge* E13 = new Edge(N1,N3);
  Edge* E25 = new Edge(N2,N5);
  Edge* E34 = new Edge(N3,N4);
  Edge* E36 = new Edge(N3,N6);
  Edge* E45 = new Edge(N4,N5);
  Edge* E46 = new Edge(N4,N6);
  Edge* E54 = new Edge(N5,N4);
  Edge* E57 = new Edge(N5,N7);
  Edge* E64 = new Edge(N6,N4);
  Edge* E67 = new Edge(N6,N7);
  Edge* E6t = new Edge(N6,Nt);
  Edge* E74 = new Edge(N7,N4);
  Edge* E76 = new Edge(N7,N6);
  Edge* E7t = new Edge(N7,Nt);
  net5.add_edge(Es1);
  net5.add_edge(Es2);
  net5.add_edge(E12);
  net5.add_edge(E21);
  net5.add_edge(E13);
  net5.add_edge(E25);
  net5.add_edge(E34);
  net5.add_edge(E36);
  net5.add_edge(E45);
  net5.add_edge(E46);
  net5.add_edge(E54);
  net5.add_edge(E57);
  net5.add_edge(E64);
  net5.add_edge(E67);
  net5.add_edge(E6t);
  net5.add_edge(E74);
  net5.add_edge(E76);
  net5.add_edge(E7t);

  Es1->change_maxflow(6);
  Es2->change_maxflow(5);
  E12->change_maxflow(6);
  E21->change_maxflow(6);
  E13->change_maxflow(3);
  E25->change_maxflow(6);
  E34->change_maxflow(5);
  E36->change_maxflow(4);
  E45->change_maxflow(3);
  E46->change_maxflow(4);
  E54->change_maxflow(3);
  E57->change_maxflow(8);
  E64->change_maxflow(4);
  E67->change_maxflow(3);
  E6t->change_maxflow(9);
  E74->change_maxflow(3);
  E76->change_maxflow(3);
  E7t->change_maxflow(1);
  net5.max_flow();

  for (auto it : net5.node_set())
    {
      cout << (*it).name() << ": "
	   << (*it).flow() << endl;
    }
  for (auto it : net5.edge_set())
    {
      cout << (*it).from_node()->name() << "->"
	   << (*it).to_node()->name() << ": "
	   << (*it).flow() << endl;
    }
  return 0;
}
