#include <iostream>
#include <stdio.h>
#include <fstream>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

class Node{
public:
    Node* left = NULL;
    Node* right = NULL;
    char myChar = '$';
    int frequency = 0 ;
    Node(char c,int f,Node* le = NULL,Node* ri = NULL)
    {
        myChar = c ;
        frequency = f ;
        left = le ;
        right = ri ;
    }
    Node();
    virtual ~Node(){}
};

class Comparator{
public:
    bool operator()(const Node* a,const Node* b)
    {
        return a->frequency > b->frequency ;
    }
};

void addCharacter(map<char,int>& domain,char c)
{
    if(domain.find(c) != domain.end())
    {
        domain[c]++;
    }
    else
        domain[c] = 0 ;
}

void populateQueue(map<char,int>& myMap,priority_queue<Node*,vector<Node*>,Comparator>& myQueue)
{
    map<char,int>::iterator iter = myMap.begin();
    while(iter!=myMap.end())
    {
        myQueue.push(new Node(iter->first,iter->second));
        iter++;
    }
}

Node* Huffman(priority_queue<Node*, vector<Node*> ,Comparator >& myQueue)
{
    if(myQueue.size() == 0)
        return nullptr ;
    Node* x ;
    Node* y ;
    while(myQueue.size() > 1)
    {
        x = myQueue.top();
        myQueue.pop();
        y = myQueue.top();
        myQueue.pop();
        cout << x->myChar << " " << y->myChar << " " << x->frequency << endl ;
        myQueue.push(new Node('$',x->frequency + y->frequency,x,y));
    }
    return myQueue.top();
}

void getCodes(Node* root,map<char,string>& codes,string code)
{
    if(root->myChar != '$')
    {
        codes[root->myChar] = code ;
    }
    else
    {
        if(root->left != NULL)
            getCodes(root->left,codes,code+"0");
        if(root->right != NULL)
            getCodes(root->right,codes,code+"1");
    }
    return ;
}

int main()
{
    priority_queue<Node*,vector<Node*>,Comparator> myQueue ;
    map<char,int> domain;
    fstream file ;
    stringstream ss ;
    Node* root ;
    file.open("input.in");
    char c ;
    while(file >> c)
    {
        ss << c ;
        addCharacter(domain,c);
    }
    populateQueue(domain,myQueue);
    root = Huffman(myQueue);
    cout << "---------------------" << endl ;
    map<char,string> codes ;
    getCodes(root,codes,"");
    map<char,string>::iterator iter = codes.begin();
    while(iter != codes.end())
    {
        cout << iter->first << " " << iter->second << endl ;
        iter++;
    }
    cout << "---------------------------------" << endl ;
    string myText = ss.str();
    for(int i = 0 ; i < myText.size() ; i++)
    {
        cout << codes[myText[i]] ;
    }
    return 0;
}
