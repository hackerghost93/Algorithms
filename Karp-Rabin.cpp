#include <iostream>
#include <stdio.h>
#include <vector>

#define BASE 256
#define MOD 257

using namespace std;

/// by math x^n =( x^(n/2) )^2
/// Divide and Conquer algorithm to find power
long long Power(int base , int exponent)
{
    if(exponent == 0)
        return 1 ;
    if(exponent == 1)
        return base ;
    if(exponent%2 == 0 )
    {
        int ret ;
        ret = Power(base,(exponent)/2);
        return ret*ret ;
    }
    else
    {
        int ret = Power(base,(exponent-1)/2);
        return base*ret*ret;
    }
}
/// Compute the start up rolling hash
/// i make by reference as a try out it's better like this
bool CheckMatch(string x , string y)
{
    if(x == y)
        return true ;
    return false ;
}
void RollingHash(long long &currentHash , string x)
{
    /// initialize hash value
    currentHash = 0 ;
    for(int i = 0 ; i < x.size() ; i++ )
    {
        currentHash = currentHash*BASE + ((x[i]));
        currentHash = currentHash % MOD ;
    }
}
void Append(long long &currentHash, char c)
{
    /// number theory when you divide mod on + ;
    currentHash = ((currentHash*BASE)%MOD + c%MOD )%MOD;
}
void SkipFirst(long long &currentHash , char c , int s)
{
    /// there was a problem because I didn't mod it before I subtract it
    /// so i need to mod twice here
    long long x = (((int)c)*Power(BASE,s-1));
    currentHash = (currentHash - x)%MOD ;
    currentHash += MOD ;
    currentHash %= MOD ;
    /// I add MOD so if it's a negative value it ends
}
#undef BASE
void KarpRabin(const string& text ,const string& pattern)
{
    int ps = pattern.size() ;
    long long hashValue = 0 ;
    long long hashText = 0;
    RollingHash(hashValue,pattern);
    RollingHash(hashText,text.substr(0,ps));
    if(hashText == hashValue && CheckMatch(pattern , text.substr(0,ps)))
    {
        cout << "found at " << 0 << endl ;
    }
    for(int i = ps ; i < text.size() ; i++)
    {
        SkipFirst(hashText,(char)text[i-ps],ps);
        Append(hashText,text[i]);
        if(hashText == hashValue && CheckMatch(pattern,text.substr(i-ps + 1 , ps)))
        {
            cout << "found at " << i << endl ;
        }
    }
}
int main()
{
    /// driver program
    freopen("input.c" , "r",stdin);
    string text , pattern ;
    getline(cin ,text);
    cout << text << endl  ;
    getline(cin,pattern);
    cout << pattern << endl  ;
    KarpRabin(text,pattern);
    return 0;
}
