#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <stdio.h>

#define INF (int)1e8

using namespace std;



int getNextNode(bool checked[],int dijkstra[],int nodes)
{
    int row = nodes+1 ;
    for(int i = 0 ; i < nodes ; i++)
    {
        if(!checked[i])
        {
            if(dijkstra[row] > dijkstra[i])
                row = i ;
        }
    }
    return row ;
}

int main()
{
    // max number of graph width is 100 node
    freopen("input.in.c","r",stdin);
    int adj_matrix[100][100];
    int nodes ,edges,source;
    int dijkstra[100];
    int parent[100];
    bool checked[100];
    /// I need here adjacency matrix not list for easy access the edge weight
    cout << "Enter the number of nodes" << endl ;
    cin >> nodes ;
    cout << "Enter the number of edges" << endl ;
    cin >> edges ;
    for(int i = 0 ; i < 100 ; i++)
    {
        /// set default dijkstra
        dijkstra[i] = INF ;
    }
    for(int i = 0 ; i < nodes ; i++)
    {
        /// set default adj_matrix
        for(int j = 0 ; j < nodes ; j++)
            adj_matrix[i][j] = INF ;
    }
    /// set booleans to false
    memset(checked,false,sizeof(checked));
    cout << "Enter the graph S D W" << endl ;
    int a , b , c;
    for(int i = 0 ; i < edges ; i++)
    {
        /// scan adjacency matrix
        cin >> a >> b >> c ;
        adj_matrix[a][b] = c;
        adj_matrix[b][a] = c;
    }
    cout << "Enter the source node" << endl ;
    cin >> source ;
    dijkstra[source] = 0 ;
    parent[source] = source ;
    for(int i = 0 ; i < nodes ;i++)
    {
        /// get the minimum unchecked node
        int node = getNextNode(checked,dijkstra,nodes);
        checked[node] = true;
        for(int j = 0 ; j < nodes ; j++)
        {
            if(j == node || checked[j])
                continue ;
                /// Dijkstra greedy algorithm is here
            if(dijkstra[node]+adj_matrix[node][j] < dijkstra[j])
            {
                /// save path with me
                parent[j] = node ;
                /// Dijkstra relaxation technique
                dijkstra[j] = dijkstra[node]+adj_matrix[node][j];
            }
        }
    }
    /// print shortest path from node to all nodes
    cout << endl << endl ;
    for(int i = 0 ; i < nodes ; i++)
    {
        cout << dijkstra[i]<< " ";
    }
    cout << endl << endl ;

    /// get the path from any node to source
    int var ;
    cout << "Get path of" << endl ;
    cin >> var;
    while(var!=source && dijkstra[var]!= INF)
    {
        cout << var << "," ;
        var = parent[var];
    }
    if(var == source)
        cout << source << endl ;
    return 0;
}
