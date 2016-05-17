#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>
#include <utility>
#include <set>

using namespace std;

vector<string> getDomain(string x)
{
    string temp ;
    set<string> mySet ;
    vector<string> domain ;
    domain.push_back("");
    for(int i = 0 ;i < x.size() ;i++)
    {
        temp.clear();
        temp += x[i];
        if(mySet.find(temp) == mySet.end())
        {
            mySet.insert(temp);
            domain.push_back(temp);
        }
    }
    return domain ;
}

void populateMapDomain(vector<string> domain , map<string,int>& encoding)
{
    encoding.clear();
    for(int i = 0 ; i < domain.size() ; i++)
    {
        encoding[domain[i]] = i-1;
    }
}

void populateMapDomain(vector<string> domain , map<int,string>& decoding)
{
    decoding.clear();
    for(int i = 1 ; i < domain.size() ; i++)
    {
        decoding[i-1] = domain[i];
    }
}

string encode(string temp , map<string,int>& myMap)
{
    stringstream coder  ;
    coder.clear();
    string t  = "";
    int code ;
    string previous ="";
    for(int i = 0 ; i <= temp.length() ; i++)
    {
        previous = t ;
        t+=temp[i];
        if(myMap.find(t) == myMap.end() && previous!="")
        {
            myMap[t] = myMap.size()-2;
            code = myMap[previous];
            coder << (char)code ;
            previous.clear();
            t.clear();
            t += temp[i];
        }
    }
    return coder.str();
}

string decode(string code , map<int,string> decodedValues)
{
    stringstream builder ;
    string previous = "";
    string current = "";
    for(int i = 0 ; i < code.length(); i++)
    {
        if(decodedValues.find((int)code[i]) == decodedValues.end())
        {
            /// doesn't exist
            current = previous + previous[0];
            decodedValues[(int)code[i]] = current ;
            builder << current ;
        }
        else
        {
            current = decodedValues[(int)code[i]];

            builder << current ;
            if(i > 0)
            {
                decodedValues[decodedValues.size()] = previous + current[0];
            }
        }

        previous = current ;
    }
    return builder.str();
}


int main()
{
    map<string,int> encodedValues ;
    freopen("input.in","r",stdin);
    string temp ;
    cin >> temp ;
    vector<string> domain = getDomain(temp);
    populateMapDomain(domain,encodedValues);

    cout << temp << endl ;
    string code = encode(temp,encodedValues) ;
    cout << "The code is " << endl;
    for(int i = 0 ; i < code.length() ; i++)
        cout <<(int)code[i] ;
    cout << endl ;

    cout << "-------------------------------------" << endl ;
    map<int,string> decodedValues ;
    populateMapDomain(domain,decodedValues);
    cout << decode(code,decodedValues);
    return 0;
}
