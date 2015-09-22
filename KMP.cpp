#include <iostream>
#include <string>

using namespace std;
/// will take order of pattern O(pattern)
//"AABAACAADAABAAABAA"
//"AABA"
void prefix(int back_to[],string pattern)
{
    int currentPointer = 0;
    back_to[0] = 0 ;
    for(int i = 1 ; i < pattern.size() ; i++)
    {
        while(currentPointer > 0 && pattern[currentPointer]!=pattern[i])
        {
            currentPointer = back_to[currentPointer-1];
        }
        if(pattern[i] == pattern[currentPointer])
        {
            back_to[i] = ++currentPointer ;
        }
        else{
            back_to[i] = 0 ;
        }
    }
}
/// will take order of the length of text O(text)
void KMP(string text , string pattern ,int back_to[])
{
    int i , j , currentPointer ;
    i = j = currentPointer = 0 ;
    while(i <= text.size())
    {
        if(currentPointer ==  pattern.size())
        {
            cout << "occurence : "<< i - currentPointer << endl ;
            currentPointer = back_to[currentPointer-1] ;
        }
        /// i need to check if i passed the last letter
        /// if at i = text.size() i continued i will get OutOfBound
        if(i == text.size())
            break ;
        ///tracing
        cout << currentPointer << " " << i << endl ;
        /// in they are a like
        if(text[i] == pattern[currentPointer])
        {
            currentPointer++;
            i++;
        }
        else
        {
            if(currentPointer > 0)
            {
                currentPointer = back_to[currentPointer-1];
            }
            else
            {
                i++;
            }
        }
    }
}

int main()
{
    string text , pattern ;
    getline(cin,text);
    cin >> pattern ;
    int back_to[pattern.size()];
    prefix(back_to,pattern);
    for(int i = 0 ; i < pattern.size() ; i++)
        cout << back_to[i] << " ";
    KMP(text,pattern,back_to);
    return 0;
}
