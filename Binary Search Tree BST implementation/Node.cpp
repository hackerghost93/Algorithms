#include "Node.h"
#include <cstddef>

Node::Node(int val)
{
    this->value = val ;
}

Node* Node::CreateNode(int val)
{
    Node* x = new Node(val,NULL,NULL);
    return x ;
}

Node::Node(int val,Node* l,Node* r)
{
    this->value = val ;
    this->right = l  ;
    this->left =  r ;
}
