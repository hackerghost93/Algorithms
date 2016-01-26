#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <bitset>
#include <stdio.h>

#define INF (int)1e6
#define Weight first
#define Parent second

using namespace std;

/// this will replace every vpii by this definition
typedef vector< pair<int,int> > vpii;

bool operator< (const pair<int,int>&x ,const pair<int,int>&y)
{
    return x.first <= y.first ;
}

vpii Dijkstra(int adj_matrix[][100] ,const int& nodes ,const int& edges ,const int& source )
{
    vpii shortestPathes(nodes);
    /// here the int int for queue is the weight first second is the node number
    /// define minimum priority queue
    priority_queue < pair<int,int>,vpii,greater< pair<int,int> > > getMin;
    /// boolean array to check if already relaxed or not
    /// priority queue will have duplicates
    bitset<100> relaxed;
    relaxed.reset();
    for(int i = 0 ; i < nodes ; i++)
    {
        shortestPathes[i].Parent = i ;
        if(i != source)
            shortestPathes[i].Weight = INF ;
        else
            shortestPathes[i].Weight = 0 ;
        /// pushing now if it's an isolated graph or not strongly connected
        getMin.push(make_pair(shortestPathes[i].Weight,i));
    }
    /// real deal start here
    for(int i = 0 ; i < nodes ; i++)
    {
        /// you could make this into one loop while the PQ is not empty
        /// if relaxed continue
        pair<int,int> temp ;
        /// get me the minimum
        while(!getMin.empty())
        {
            temp = getMin.top();
            getMin.pop();
            if(!relaxed[temp.first])
                break ;
        }
        /// i will relax this
        relaxed[temp.second] = true ;
        for(int j = 0 ; j < nodes ;j++)
        {
            /// if already relaxed or myself
            if(j == temp.second && !relaxed[j])
                continue ;
            /// relaxation condition
            if(adj_matrix[temp.second][j]+temp.first < shortestPathes[j].Weight)
            {
                shortestPathes[j].Weight = adj_matrix[temp.second][j]+temp.first;
                shortestPathes[j].Parent = temp.second ;
                getMin.push(make_pair(shortestPathes[j].Weight,j));
            }
        }
    }
    return shortestPathes;
}
/// driver program
int main()
{
    freopen("input.c","r",stdin);
    int adj_matrix[100][100];
    int nodes , edges , from , to , w , source ;
    cout << "Enter the number of nodes and edges" << endl ;
    cin >> nodes >> edges ;
    cout << "Enter bi-direction graph from to weight" << endl ;
    memset(adj_matrix,INF,sizeof(adj_matrix));
    for(int i = 0 ; i < edges ; i++)
    {
        cin >> from >> to >> w ;
        adj_matrix[from][to] = w;
        adj_matrix[to][from] = w;
    }
    cout << "Enter the source for SP" << endl ;
    cin >> source ;
    vpii x = Dijkstra(adj_matrix,nodes,edges,source);
    printf("Weight\t Parent\t\n");
    for(int i = 0 ; i < nodes ; i++)
    {
        cout << x[i].first << "        " << x[i].second << endl ;
    }
    return 0;
}
