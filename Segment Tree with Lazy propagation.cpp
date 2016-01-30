#include <iostream>
#include <cstring>

#define Invalid 1e8

using namespace std;
int build(int arr[],int segmentTree[],int low , int high , int pos = 0)
{
    ///Validation for the start condition
    if(low > high)
        swap(low,high);
    ///Leaf node stopping condition
    if(low == high)
        return segmentTree[pos]=arr[low];
    ///Recursive call
    return segmentTree[pos] =
                min(build(arr,segmentTree,low,(low+high)/2,2*pos + 1)
                    ,build(arr,segmentTree,((low+high)/2)+1,high,2*pos + 2));
}
int query(int segmentTree[],int lazyProp[],int queryLow,int queryHigh,int low ,int high,int pos = 0)
{
    ///Validation for the first call
    if(queryLow > queryHigh)
        swap(queryLow,queryHigh);
    ///Validation for the first call
    if(low > high)
        swap(low,high);
    ///Check if already modified or lazy propagation on interval
    if(lazyProp[pos] != 0)
    {
        ///Lazy Propagate in this node
        segmentTree[pos]+=lazyProp[pos];
        ///Propagate for children nodes if not a leaf
        if(low != high)
        {
            lazyProp[2*pos+1]+=lazyProp[pos];
            lazyProp[2*pos+2]+=lazyProp[pos];
        }
        ///Remove modification after it is done to this node
        lazyProp[pos] = 0 ;
    }
    ///No Overlap
    if(high < queryLow || low > queryHigh)
         return Invalid ;
    ///Total Overlap
    if(high <= queryHigh && low >= queryLow)
        return segmentTree[pos];
    ///Partial Overlap otherwise
        /// get the minimum from left child and right child
        /// I can't set segmentTree from come back .. comeback might be invalid
        return min(query(segmentTree,lazyProp,queryLow,queryHigh,low,(low+high)/2,2*pos+1),
                   query(segmentTree,lazyProp,queryLow,queryHigh,(low+high)/2 + 1,high,2*pos+2));
}
void update(int segmentTree[],int lazyProp[],int delta,
            int queryLow,int queryHigh,int low , int high ,int pos = 0)
{
    ///Same 3 cases : total overlap,partial overlap , or no overlap
    ///propagate
    if(lazyProp[pos]!=0)
    {
        segmentTree[pos] += lazyProp[pos];
        if(high!=low)
        {
            lazyProp[2*pos + 1] += lazyProp[pos];
            lazyProp[2*pos + 2] += lazyProp[pos];
        }
        lazyProp[pos] = 0 ;
    }
    ///No overlap case
    if(low > queryHigh || high < queryLow)
        return ;
    ///Total overlap case
    if(low >= queryLow && high <= queryHigh)
    {
        ///My update. the lazy tree is sure to be zero at this node
        segmentTree[pos] += delta ;
        if(high!=low)
        {
            ///Get this propagation to children
            lazyProp[2*pos + 1] += delta;
            lazyProp[2*pos + 2] += delta;
        }
        return ;
    }
    ///partial
    update(segmentTree,lazyProp,delta,queryLow,queryHigh,low,(low+high)/2,2*pos+1);
    update(segmentTree,lazyProp,delta,queryLow,queryHigh,(low+high)/2 +1,high,2*pos+2);
    ///Sure not a leaf would have returned.
    ///For leaf node it's a total or none overlap case.
    segmentTree[pos] = min(segmentTree[2*pos+1],segmentTree[2*pos+2]);
}
int main()
{
    int n ;
    cout << "Enter the number of elements" << endl ;
    cin >> n ;
    int arr[n];
    for(int i = 0; i < n ;i++)
        cin >> arr[i];
    int segmentTree[4*n];
    int lazyProp[4*n];
    memset(lazyProp,0,sizeof(lazyProp));
    build(arr,segmentTree,0,n-1);
    for(int i = 0 ; i < 4*n ;i++)
    {
        cout << segmentTree[i] << ",";
    }
    cout << endl ;
    for(int i = 0 ; i < 2 ; i++)
    {
        int temp ,l ,h;
        cout << "Enter delta" << endl ;
        cin >> temp ;
        cout << "Enter range" << endl ;
        cin >> l >> h ;
        update(segmentTree,lazyProp,temp,l,h,0,n-1);
        for(int i = 0 ; i < 2*n ; i++)
            cout << lazyProp[i] << ",";
        cout << endl ;
        for(int i = 0 ; i < 2*n ;i++)
            cout << segmentTree[i] << ",";
        cout << endl << endl ;
    }
    cout << "--------------" << endl ;
    for(int i = 0 ; i < 2 ; i++)
    {
        int l , h ;
        cout << "Enter range" << endl ;
        cin >> l >> h ;
        cout <<"Answer is " <<query(segmentTree,lazyProp,l,h,0,n-1) << endl ;
        for(int i = 0 ; i < 2*n ; i++)
            cout << lazyProp[i] << ",";
        cout << endl << endl ;
        for(int i = 0 ; i < 2*n ;i++)
            cout << segmentTree[i] << ",";
        cout << endl << "--------------" << endl ;
    }

    return 0;
}
