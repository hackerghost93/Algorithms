#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

string encode(string x)
{
    stringstream builder ;
    int counter = 1 ;
    for(int i = 1 ; i < x.length()+1 ; i++)
    {
        if(x[i] != x[i-1])
        {
            if(counter >= 4)
            {
                builder << x[i-1] << "!" << counter ;
            }
            else
                builder << x[i-1] ;
            counter = 1 ;
        }
        else
            counter++;
    }
    return builder.str();
}

int power(int base , int exp)
{
    int num = 1 ;
    for(int i = 0 ; i < exp ; i++)
        num *=base ;
    return num ;
}

int getNumber(string x,int iter)
{
    int i ;
    int sign = 1;
    if(x[iter] == '-')
    {
        sign = -1;
        iter++;
    }
    for(i = iter;i <= x.length() && x[i] >= '0' && x[i] <= '9' ;i++)
     ;
    int num = 0;
    int len = i - iter;
    for(int j = 0 ; j < len ; j++)
    {
        int temp = power(10,len-j-1);
        num+=temp*(x[iter+j]-'0');
    }
    return num*sign ;

}

vector<string> getWords(string x)
{
    vector<string> words ;
    istringstream iss(x)  ;
    string token ;
    while(getline(iss,token,','))
    {
        words.push_back(token);
    }
    return words ;
}

int isCompound(string word)
{
    for(int i = 0;  i < word.length() ;i++)
    {
        if(word[i] == '!' && i!= word.length()-1 )
            return i ;
    }
    return 0 ;
}

int getNumber(string num)
{
    int ans = 0 ;
    for(int i = 0 ; i < num.length() ; i++)
    {
        ans += (num[i]-'0')*power(10,num.length()-1-i);
    }
    return ans ;
}

pair<string,int> getCompound(string word)
{
    istringstream iss(word);
    pair<string,int> ret ;
    string num ;
    getline(iss,ret.first,'!');
    iss >> num ;
    ret.second = getNumber(num);
    return ret ;
}

vector<string> decode(string input)
{
    int compoundIndex ;
    vector<string> bytes ;
    vector<string> words = getWords(input);
    pair<string,int> compound ;
    for(int i = 0 ; i < words.size() ; i++)
    {
        if(compoundIndex = isCompound(words[i]) > 0)
        {
            compound = getCompound(words[i]);
            for(int i = 0 ; i < compound.second ; i++)
            {
                bytes.push_back(compound.first);
            }
        }
        else
        {
            bytes.push_back(words[i]);
        }
    }
    return bytes ;
}

int differentialEncoding(int x[][5] , int row , int column)
{
    int past ;
    int temp ;
    for(int i = 0 ; i < row ; i++ )
    {
        past = x[i][0];
        for(int j = 1 ; j < column ; j++)
        {
            temp = x[i][j];
            x[i][j] = x[i][j]-past;
            past = temp ;
        }
    }
}

string parserRow(int x[][5] , int row , int columns)
{
  stringstream builder ;
    int counter = 1 ;
    for(int i = 1 ; i < columns ; i++)
    {
        if(x[row][i] != x[row][i-1])
        {
            if(counter >= 4)
            {
                builder << x[row][i-1] << "!" << counter  ;
            }
            else
                builder << x[row][i-1] ;
            builder << "," ;
            counter = 1 ;
        }
        else
            counter++;
    }
    if(counter >= 4)
            {
                builder << x[row][columns-1] << "!" << counter << ",";
            }
    else
        builder << x[row][columns-1] << "," ;
    counter = 1 ;
    return builder.str();
}

vector<int> dedifferential(const vector<string>& diff)
{

    vector<int> samples ;
    if(diff.empty())
        return samples ;
    samples.push_back(getNumber(diff[0]));
    int temp ;
    for(int i = 1 ; i < diff.size() ; i++)
    {
        temp = getNumber(diff[i]);
        samples.push_back(temp+samples[i-1]);
    }
    return samples ;
}

int main()
{
    int x[4][5];
    ifstream file("input.in");
    if(file.is_open())
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j=0; j<5;j++)
            {
                file >> x[i][j];

            }

        }
    }
    file.close();
    cout << "Original Array" << endl ;
    for(int i = 0 ; i < 4 ;i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            cout << x[i][j] << "," ;

        }

        cout << endl ;

    }
    cout << "-------------------------------------" << endl;
    cout << "Differential Encoding" << endl ;
    differentialEncoding(x,4,5);
    for(int i = 0 ; i < 4 ;i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            cout << x[i][j] << "," ;
        }
        cout << endl ;
    }
    cout << "-------------------------------------" << endl ;
    cout << "Applying Run Length Encoding" << endl ;
    vector <string> Codes ;
    for(int i = 0 ; i < 4 ;i++)
    {
        string p = parserRow(x,i,5) ;
        cout <<  p << endl ;
        Codes.push_back(p);
    }
    cout << "-------------------------------------" << endl ;
    cout << "The reconstruction of Array" << endl ;
    vector<string> diffDecoded ;
    vector<int> samples ;
    for(int i = 0 ; i < Codes.size() ; i++)
    {
        diffDecoded = decode(Codes[i]);
        samples = dedifferential(diffDecoded);
        for(int i = 0 ; i < samples.size();i++)
        {
            if(i+1 == samples.size())
                cout << samples[i] << endl ;
            else
                cout << samples[i] << ",";
        }
    }
    return 0;
}
