#include <iostream>

using namespace std;
long long Power(int b , int e )
{
    long long ans ;
    if(e == 1) return b ;
    if(e%2 == 0)
    {
        ans = Power(b,e/2) ;
        return ans*ans ;
    }
    else
    {
        ans = Power(b,e/2) ;
        return ans*ans*b ;
    }
}
int main()
{
    cout << "Enter the Base & exponent" << endl ;
    int b , e ;
    long long ans ;
    cin >> b >> e ;
    cout << Power(b,e);
    return 0;
}
