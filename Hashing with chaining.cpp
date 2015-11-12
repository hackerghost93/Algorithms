#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

/// this is hashing with chaining as it has a bad theoretical complexity
/// it has a very good practical complexity
int hashDivisionMethod(int key,int m)
{
    /// m : is the size of hash table and it must be prime and not close
    ///     to a name power of 2 or 10
    return key%m ;
}
uint32_t hashMultiplicationMethod(uint32_t key , int m )
{
    /// m must be a power of 2 and r is log(m)
    /// random must be odd
    /// random must be in range 2^r - 1 ... 2^r
    /// w is the word length on the machine most machine 32
    int r = 6 ;
    int w = 32;
    return ((UINT32_C(2654435761)*key))>>(32 - 6);
}
int hashUniversalMethod(int key , int m )
{
    /// 2 random numbers
    int random1 , random2 ;
    /// p random prime number bigger than the universe which contains the key
    /// random 1 must not be equal to 1
    /// for large p -> probability of collision is 1/m ... a varies from 1-> p
    int p ;
    return ((random1*key + random2)%p)%m ;
}
void insertToTable(vector < vector<int> >& hashtable , int key , int value , int method)
{
    if(method == 1)
        {
            hashtable[hashDivisionMethod(key,m)].push_back(value);
        }
        else if(method == 2)
        {
            hashtable[hashMultiplicationMethod(key,m)].push_back(value);
        }
        else
            hashtable[hashUniversalMethod(key,m)].push_back(value);
}
void rebuild(vector < vector<int> >& hashtable , int newSize , int method)
{
    vector < vector<int> > x(newSize);
    for(int i = 0 ; i < hashtable.size() ; i++)
    {
        for(int j = 0 ; j < hashtable[i].size() ; j++)
        {
            insertToTable(x,i,hashtable[i][j] ,method);
        }
    }
}
void deleteFromTable(vector < vector<int> >& hashtable , int key , int value , int method)
{
        if(method == 1)
        {
            int key = hashtable[hashDivisionMethod(key,hashtable.size())] ;
        }
        else if(method == 2)
        {
            hashtable[hashMultiplicationMethod(key,m)].push_back(value);
        }
        else
            hashtable[hashUniversalMethod(key,m)].push_back(value);
}

int main()
{
    /// I guess there is 2 implementation for it in c++
    /// vectors and list .. but i guess a vector will be better
    /// Probability of Collision in chaining case is n/m
    /// and it takes order of O(1+ n/m )
    int m = 32 ;
    int n ;
    int method , key , value;
    vector < vector<int> > hashtable(m);
    cout << "Enter the number of keys" << endl ;
    cin >> n ;
    cout << "choose prehash function" << endl ;
    cout << "1)Division Method " << endl ;
    cout << "2)Multiplication Method" << endl ;
    cout << "3)Universal Method" << endl ;
    cin >> method ;
    for(int i = 0 ; i < n ; i ++ )
    {
        cout << "Enter key and value" << endl ;
        cin >> key >> value ;


        if(n > m)
        {
            rebuild(hashtable,m*2) ;
        }
        else if(n == m/4)
        {
            rebuild(hashtable , m/2 );
        }
    }
    return 0;
}
