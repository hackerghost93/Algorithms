#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <map>
#include <sstream>

using namespace std;
class Node
{
public:
    char myChar = '$';
    long double probability = -1;
    vector<Node*> children  ;
    Node(){}
    Node(char s,long double prob)
    {
        myChar = s ;
        probability = prob;
//        children = new vector<Node*>;
    }
    void AddChild(Node* x)
    {
        children.push_back(x);
    }
    Node* getMaxChild()
    {
        if(children.size() == 0)
            return NULL ;
        Node* x = children[0];
        for(int i = 1 ; i < children.size() ;i++)
        {
            if(x->probability < children[i]->probability )
            {
                x = children[i];
            }
        }
        return x ;
    }
    int sizeChild()
    {
        return children.size();
    }
};

vector< pair<char,long double> >  getDomain(string x)
{
    map<char,int> occMap ;
    vector< pair<char,long double> > occVector ;
    for(int i = 0 ; i < x.size() ; i++)
    {
        if(occMap.find(x[i]) == occMap.end())
        {
            occMap[x[i]] = 1;
        }
        else
            occMap[x[i]]++;
    }
    map<char,int>::iterator iter = occMap.begin();
    while(iter != occMap.end())
    {
        occVector.push_back(
                make_pair(iter->first , iter->second / (double)x.size())
                            );
        iter++ ;
    }
    return occVector ;
}

void TunstallTree(Node* root,vector< pair<char,long double> >& domain , int n )
{
    int leafs = 1 ;
    int m = domain.size() ;/// number of symbols
    Node* temp = root ;
    Node* t ;
    do{
        for(int i = 0 ; i < m ; i++)
        {
            temp->AddChild(new Node(domain[i].first,domain[i].second));
        }
        temp = temp->getMaxChild();
        leafs+= m - 1 ;
    }while(leafs <= (1<<n)-m  );
}
void TraverseTree(Node*root,vector<string>& codes,string code = "")
{
    if(root->sizeChild() == 0)
    {
        codes.push_back(code);
    }
    for(int i = 0 ; i < root->sizeChild() ; i++)
    {
        TraverseTree(root->children[i],codes,code+root->children[i]->myChar);
    }
}
int main()
{
    fstream file ;
    file.open("input.in");
    char temp ;
    stringstream ss ;
    while(file >> temp )
    {
        ss << temp ;
    }
    string text = ss.str();
    vector< pair<char,long double> > domain =  getDomain(text);
    Node * root = new Node() ;
    TunstallTree(root,domain,4);
    vector<string> codes ;
    TraverseTree(root,codes);
    for(int i = 0 ; i < codes.size() ; i++)
    {
        cout << codes[i] << " code " << i << endl ;
    }
    return 0;
}
