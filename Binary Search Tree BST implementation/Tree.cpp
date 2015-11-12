#include "Tree.h"
#include <iostream>
#include <cstddef>

using namespace std ;


Node* InsertValue(Node* root ,int key)
{
    if(root == NULL)
        return  Node::CreateNode(key);
    else if(root->value == key)
    {
        return root ;
    }
    else if(root->value > key)
        root->left = InsertValue(root->left , key);
    else
        root->right = InsertValue(root->right , key);
    return root ;
}
void InorderTraversal(Node* root)
{
    /// this is sorting the BST
    /// as Inorder Traversal is left - root - right
    if(root == NULL)
        return ;
    InorderTraversal(root->left);
    cout << root->value << " " ;
    InorderTraversal(root->right);
}

int Count(Node*root)
{
    /// just traversing every node
    if(root == NULL)
        return 0;
    return 1+Count(root->left)+Count(root->right);
}

Node* Find(Node*root,int key)
{
    /// this implicit if condition is better
    if(root ==NULL || root->value == key)
    {
        return root ;
    }
    /// I had to only get one path of search ..
    /// I used to traverse all the graph for it
    if(root->value > key)
        return  Find(root->left , key);
    else
        return Find(root->right , key );
}
