#include "Node.h"
#include "Edge.h"
#include "Set.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
  Set<Node*> nodes_;
  Set<Edge*> edges_;
  Node* node_ptr1 = new Node();
  Node* node_ptr2 = new Node();
  node_ptr1->change_name("Nod 1");
  node_ptr2->change_name("Nod 2");
  Edge* edge_ptr = new Edge(node_ptr1,node_ptr2);
  nodes_.add_member(node_ptr1);
  nodes_.add_member(node_ptr2);
  edges_.add_member(edge_ptr);
  
  for (unsigned int i = 0; i < nodes_.size(); ++i)
    cout << nodes_[i]->name() << endl;

  cout << "Edge from: " << edges_[0]->from_node()->name() << endl;
  cout << "Edge to: " << edges_[0]->to_node()->name() << endl;
  for (unsigned int i = 0; i < node_ptr1->in_edges().size(); ++i)
    cout << "Node 1 in Edge from: " << node_ptr1->in_edges()[i]->from_node()->name() << endl;
  return 0;
}
