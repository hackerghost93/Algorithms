#include <iostream>
#include <cstdlib>
#include "Tree.h"

using namespace std;


int main()
{
    Node* root = Node::CreateNode(42);
    cout << root->value << " ";
    for(int i = 0 ; i < 7 ; i++)
    {
        int z  = rand()%100 ;
        cout << z << endl ;
        InsertValue(root,z);
    }
    cout << endl << endl ;
    InorderTraversal(root);
    cout << endl << endl ;
    cout << Count(root) << endl ;
    cout << endl << endl ;
    int checker ;
    cin >> checker ;
    if(Find(root,checker)!=NULL)
    cout << Find(root,checker);


    return 0;
}
