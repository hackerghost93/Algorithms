#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
#include <stdlib.h>

#define INF 1e8

using namespace std;

class Node
{
public:
    int from ;
    int to ;
    int weight ;
    Node(int f , int t ,int w)
    {
        this->from = f ;
        this->to = t ;
        this->weight = w ;
    }
};

class Parent{
public:
    int parent ;
    int currentDistance;
    Parent()
    {
        this->parent = -1 ;
        this->currentDistance = INF ;
    }
};

class Graph{
private:
    int vertices ;
    int edges ;
    vector< Node > edgeList;
public :
    Graph(int v , int e)
    {
        this->vertices = v ;
        this->edges = e ;
    }
    void AddEdge(int from , int to , int weight);
    vector<Parent> BellmanFord(int source);
    void GetPath(const vector<Parent>& x,int source,int destination,int node,vector<int>& path);
    bool checkNegativeCycle(vector<Parent> x);
};
void Graph::AddEdge(int from,int to,int weight)
{
    // new Node will return the pointer to Node
    // just calling the constructor will return it as an object
    edgeList.push_back(Node(from,to,weight));
    edgeList.push_back(Node(to,from,weight));
}

vector<Parent> Graph::BellmanFord(int source)
{
    vector<Parent> distances(this->vertices,Parent());
    distances[source].currentDistance = 0 ;
    for(int i = 0 ; i < vertices ; i++)
    {
        for(int j = 0 ; j < edgeList.size();j++)
        {
            // relaxation condition
            if(distances[edgeList[j].to].currentDistance >
                    distances[edgeList[j].from].currentDistance
                        +edgeList[j].weight
               )
            {
                /// relax the graph
                distances[edgeList[j].to].currentDistance =
                    distances[edgeList[j].from].currentDistance
                        +edgeList[j].weight ;
                /// set the parent
                distances[edgeList[j].to].parent = edgeList[j].from ;
            }
        }
    }
    return distances ;
}


void Graph::GetPath(const vector<Parent>& x,int source,int destination,int node,vector<int>& path)
{
    if(x[node].parent == -1 || node == source)
    {
        path.push_back(node);
        return ;
    }
    GetPath(x,source,destination,x[node].parent,path);
    path.push_back(node);
}

bool Graph::checkNegativeCycle(vector<Parent> x)
{
    for(int i = 0 ; i < this->edges ; i++)
    {
        if(x[edgeList[i].to].currentDistance >
                x[edgeList[i].from].currentDistance + edgeList[i].weight
           )
           return true ;
    }
    return false ;
}



int main()
{
    /// test drive
    freopen("input.c","r",stdin);
    Graph g = Graph(7,9);
    int f , t , w ;
    for(int i = 0 ; i < 9 ; i++)
    {
        cin >> f >> t >> w ;
        g.AddEdge(f,t,w);
    }
    vector<Parent> x = g.BellmanFord(0);
    for(int i = 0 ; i < x.size();i++)
        cout <<"current Node " << i << "->dist:par "<< x[i].currentDistance << ":" << x[i].parent << endl ;

    cout << "-------------------------------" << endl ;
    vector<int> path;

    /// can't work if there is negative cycle
    g.GetPath(x,0,6,6,path);
    for(int i = 0 ; i < path.size();i++)
        cout << path[i] << ",";
    cout << endl ;

    cout << "------------------------------" << endl ;
    cout << g.checkNegativeCycle(x);
    return 0;
}
