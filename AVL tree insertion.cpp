#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

///AVL is the same as the BST but it's always balanced using Rotation Property
/// Rotation takes linear time

using namespace std;
class node{
    public :
    /// Default constructor
    node();
    node(int value);
    /// Members & variables
    int value ;
    int height ;
    node* left ;
    node* right  ;
};
node::node()
{
    height = 0 ;
    left = NULL ;
    right = NULL ;
}
node::node(int val)
{
    height = val ;
    left = NULL ;
    right = NULL ;
}
void Show(node* p, int indent=0)
{
    if(p != NULL) {
        if(p->left) Show(p->left, indent+4);
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout<< p->value<< "\n ";
        if(p->right) Show(p->right, indent+4);

    }
}
void getHeight(node* root)
{
    if(root == NULL)
        return ;
    if(root->right == NULL && root->left == NULL)
        root->height = 0 ;
    else if(root->right == NULL)
        root->height = (root->left->height) + 1 ;
    else if(root->left ==NULL)
        root->height = (root->right->height) + 1 ;
    else root->height = max(root->right->height , root->left->height) + 1;
}
void InorderTraversal(node* root)
{
    if(root == NULL)
        return ;
    if(root->left != NULL)
        InorderTraversal(root->left);
    cout << root->value <<":" << root->height <<  "," ;
    if(root->right != NULL)
        InorderTraversal(root->right);
}
void PreorderTraversal(node* root)
{
    if(root == NULL)
        return ;
    cout << root->value << ":" << root->height << "," ;
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
}
node* leftRotate(node* ptr)
{
    cout << "LEFT ROTATE " << ptr->value << endl ;
    node* nextroot = ptr->right ;
    ptr->right = nextroot->left ;
    nextroot->left = ptr ;
    getHeight(ptr);
    getHeight(nextroot);
    return nextroot ;
}
node* rightRotate(node* ptr)
{
    cout << "RIGHT ROTATE" << ptr->value << endl ;
    node* nextroot = ptr->left ;
    ptr->left = nextroot->right ;
    nextroot->right = ptr ;
    getHeight(ptr);
    getHeight(nextroot);
    return nextroot ;
}
int getBalance(node* root)
{
    if(root->left == NULL )
        return (root->right->height)*-1 ;
    else if(root->right == NULL)
        return root->left->height ;
    else if(root->left == NULL && root->right ==NULL )
        return 0 ;
    return (root->left->height) - root->right->height;
}
node* Insert(node* root , node* current)
{
    if(root == NULL)
    {
        root = current ;
        root->height = 0 ;
        return root ;
    }
    else if(root->value == current->value)
        return root ;
    else
    {
        /// insertion method
        cout << "Parent Value " << root->value << " " << "child value " << current->value << endl ;
        if(current->value > root->value)
            root->right = Insert(root->right , current) ;
        else if(current->value < root->value)
            root->left = Insert(root->left , current);
        /// end of insertion method
        getHeight(root);
        /// left left case
        if(getBalance(root) > 1 && (root->left->value) > current->value )
        {
            cout << "please left right rotate " << root->value << endl ;
            root = rightRotate(root);
        }
        /// right right case
        /// the double balance violation is on the right & my new input on the right of it
        else if(getBalance(root) < -1 && (root->right->value) < current->value)
        {
            cout << "please left left rotate " << root->value << endl ;
            root = leftRotate(root);
        }
        /// Right left case
        else if(getBalance(root) < -1)
        {
            //rightRotate(root);
            cout << "Right left" << root -> value << endl ;
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
        /// left Right Case
        else if(getBalance(root) > 1)
        {
            cout << "Left Right" << root->value  << endl ;
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
        return root ;
    }
}
int main()
{

    node* root = (node*)malloc(sizeof(node));
    node* x = (node*)malloc(sizeof(node));
//    x->value = rand()%100+1;
    x->value = rand()%100 + 1 ;
    x->left = NULL ;
    x->right = NULL ;
    //cout << x->value << "root value " << endl ;
    root = Insert(NULL , x);
    InorderTraversal(root);
    cout << endl ;
    /// trying to insert to code
    for(int i = 25 ; i >1 ; i--)
    {
        node* x = (node*)malloc(sizeof(node));
        x->value = rand() %100 + 1;
        x->left = NULL ;
        x->right= NULL ;
        cout << x->value << "myNewValue" << endl ;
        root = Insert(root , x);
        cout << "start inorder" << endl ;
        InorderTraversal(root);
        cout << "end inorder" << endl ;
        cout << endl ;
    }
//    Insert(root,2);
//    Insert(root,3) ;
//    Insert(root,4) ;
//    Insert(root,5) ;
//    Insert(root,6);
    cout << "----------------------------" << endl ;
    PreorderTraversal(root);
    cout << endl ;
    cout << "----------------------------" << endl ;
    Show(root,0);
    return 0;
}
