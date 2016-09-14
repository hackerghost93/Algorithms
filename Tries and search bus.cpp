#include <iostream>
#include <vector>


using namespace std;

/// Order is text*|norm the patterns (the longest pattern)|
/// the problem is the number of edges of tries is O( total length of patterns )
/// shit memory limit exceed in this
/// for genome this is impossible match as the total length is O(10^12)
class Node{
public:
    char character ;
    bool isLeaf ;
    vector<Node*> neighbors ;
    Node(char value,bool leaf = false):character(value),isLeaf(leaf)
    {
        cout << "Node created" << endl ;
        cout << this->character << " " << this->isLeaf << endl ;
    }
    Node* isNeighbor(char x)
    {
        for(int i = 0 ; i < this->neighbors.size() ; i++)
        {
            if(neighbors[i]->character == x)
                return neighbors[i];
        }
        return NULL ;
    }

    Node* addNeighbor(char x,bool leaf = false)
    {
        Node* temp ;
        if((temp = isNeighbor(x)) == NULL)
        {
            temp = new Node(x,leaf);
            this->neighbors.push_back(temp);
        }
        else // not null but now it's a leaf
        {
            if(leaf == true)
                temp->isLeaf = leaf;
        }
        return temp ;
    }
};

class Trie{
private:
    Node* root ;
    size_t patterns = 0 ;
public:
    Trie(){
        cout << "Trie created" << endl ;
    }
    ~Trie(){
        cout << "Trie destroyed" << endl ;
    }
    Node* getRoot()
    {
        return this->root ;
    }
    void setRoot(Node* node)
    {
        this->root = node ;
    }
    Node* insert(string pattern)
    {
        Node* current = this->getRoot();
        for(int i = 0 ; i < pattern.size() ; i++)
        {
            if(i == pattern.size() -1)
                current = current->addNeighbor(pattern[i],true);
            else
                current = current->addNeighbor(pattern[i]);
        }
    }
    void incrementPatterns()
    {
        this->patterns++ ;
    }
    void print(Node* root)
    {
        /// BFS printing
        cout << root->character << endl ;
        for(int i = 0 ; i < root->neighbors.size() ; i++)
        {
            print(root->neighbors[i]);
        }
    }

    bool search(Node* root,string pattern,int index = 0)
    {
        if(index == pattern.length() && root->isLeaf)
        {
            return true ;
        }
        if(index == pattern.length())
            return false ;
        Node* next ;
        if((next = root->isNeighbor(pattern[index])) != NULL)
        {
            return search(next,pattern,index+1);
        }
        else
            return false ;
    }


    bool searchText(Node* root ,string text)
    {
        Node* step ;
        for(int i = 0 ; i < text.length() ; i++)
        {
            step = root ;
            for(int j = i ; j < text.length() ; j++)
            {
                if((step = step->isNeighbor(text[j])) != NULL)
                {
                    if(step->isLeaf)
                    {
                        cout << "pattern found" << endl ;
                        for(int k = i ; k <= j ; k++)
                            cout << text[k];
                        cout << endl ;
                        cout << "--------------------------" << endl ;
                    }
                }
                else
                    break;
            }

        }
    }


};

int main()
{
    int n ;
    Trie* myTrie = new Trie();
    Node* root = new Node('$');
    myTrie->setRoot(root);
    string pattern ;
    string text ;
    cout << "Enter the text" << endl ;
    cin >> text ;
    cout << "Enter the number of patterns" << endl ;
    cin >> n ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Enter pattern" << endl ;
        cin >> pattern ;
        myTrie->insert(pattern);
    }
//    myTrie->print(root);
//    while(true)
//    {
//        cout << "Enter pattern you want to search" << endl ;
//        cin >> pattern ;
//        cout << myTrie->search(root,pattern);
//    }
    myTrie->searchText(root,text);
    return 0;
}
