#include <iostream>
#include <cstring>

using namespace std;

int needed = 3 ;
int arr [] = {1,1,2,3,4};
const int n = 5 ;
bool visited[n] ;
int selection[n];
void Print()
{
    for(int i = 0 ; i< needed ; i++)
    {
        cout << selection[i] << " " ;
    }
    cout << endl ;
}
void Permutation(int node)
{
    if(node == needed)
    {
        Print();
        return ;
    }
    for(int i = 0 ; i < n ; i++)
    {
        if(!visited[i])
        {
            visited[i] = true ;
            selection[node] = arr[i];
            Permutation(node+1);
            visited[i] = false ;
        }
    }
}
int main()
{
    memset(visited,false,sizeof(visited));
    Permutation(0);
    return 0;
}
