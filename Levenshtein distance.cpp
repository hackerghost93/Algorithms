#include <iostream>
#include <cstring>
using namespace std;
/// keep holding one and try the 3 operations on the other
int dp[50][50];
int Leveinstein_algorithm(const string &a,const string &b,int i,int j)
{
    /// invalid case
    /// the rest of the other string to be returned
    if(i >= a.size())
        return b.size()-j ;
    if(j >= b.size())
        return a.size()-i ;
    /// base case
    if(a[i] == b[j])
        return Leveinstein_algorithm(a,b,i+1,j+1);
    int ret1 , ret2 , ret3 ;
    if(dp[i][j] != -1)
        return dp[i][j];
    /// insert case
    ret1 = Leveinstein_algorithm(a,b,i+1,j)+1;
    /// delete case
    ret2 = Leveinstein_algorithm(a,b,i,j+1)+1 ;
    /// substitution case
    ret3 = Leveinstein_algorithm(a,b,i+1,j+1)+1 ;
    return dp[i][j] = min(ret1,min(ret2,ret3));

}


int main()
{
    memset(dp,-1,sizeof(dp));
    string a , b ;
    cin >> a >> b ;
    if(a.size()<b.size())
        swap(a,b);
    cout << Leveinstein_algorithm(a,b,0,0);
    return 0;
}
