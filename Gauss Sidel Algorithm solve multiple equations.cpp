#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    // 10 is the max number of equations
    vector < vector<double> > coefficients(10) ;
    int order ;
    cout << "Enter the number of variables" << endl ;
    cin >> order ;
    double temp ;
    double tolerance;
    for(int i = 0 ; i <order ;++i)
    {
        cout << "Enter the " << i+1 << " equation coefficients" << endl ;
        for(int j = 0 ; j <= order ; j++)
        {
            cin >> temp ;
            coefficients[i].push_back(temp);
        }
    }
    cout << "Enter the tolerance" << endl ;
    cin >> tolerance ;
    double maxTolerance = 1000.0 ;
    vector <double> previous_values(order,0) ;
    vector <double> new_values(order,0) ;
    while(maxTolerance > tolerance)
    {
        for(int i = 0 ; i < order ; i++)
        {
            previous_values[i] = new_values[i];
        }
        for(int i = 0 ; i < order ;i++)
        {
            new_values[i] = 0 ;
            new_values[i] += coefficients[i][order];
            for(int j = 0 ; j < order ; j++)
            {
                if(j==i)
                    continue ;
                else if(j > i)
                {
                    new_values[i] -= coefficients[i][j]*previous_values[j];
                }
                else
                    new_values[i] -= coefficients[i][j]*new_values[j];
            }
            new_values[i]/=coefficients[i][i];
            if(i == 0)
                maxTolerance = abs(new_values[0] - previous_values[0]);
            else
                maxTolerance = max(maxTolerance,abs(new_values[i] - previous_values[i]));

        }
    }
    cout << "Answers" << endl ;
    for(int i = 0 ; i < order ; i++ )
        cout << new_values[i] << endl ;

    return 0;
}
