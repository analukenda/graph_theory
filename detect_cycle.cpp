#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>

using namespace std;
#define INF 100200
const int MAX = 20;

vector<int> v[INF];


void brid(int i, int j){
    v[i].push_back(j);
    v[j].push_back(i);
}


int struk(int n){
    
    int rez = INT_MAX;
    for (int i = 0; i < n; i++)
    {

        
        vector<int> d(n, (int)(1e9));
        vector<int> par(n, -1);

        
        d[i] = 0;
        queue<int> q;

        q.push(i);

      
        while (!q.empty())
        {

           
            int a = q.front();
            q.pop();

            
            for (int b : v[a])
            {

                
                if (d[b] == (int)(1e9))
                {
                    d[b] = 1 + d[a];
                    par[b] = a;
                    q.push(b);
                }

               
                else if (par[a] != b && par[b] != a)
                    rez = min(rez, d[a] + d[b] + 1);
            }
        }
    }

    
    if (rez == INT_MAX)
        return -1;

    
    else
        return rez;
}


int main()
{
    int rez,i,j;

    ifstream stream;
    string dat;
    cout << "Unesite ime datoteke: ";
    cin >> dat;
    stream.open(dat);

    int n = 0;
    stream >> n;
    int matrica[MAX][MAX];
    stream.ignore(1, '\n');

    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            stream >> matrica[i][j];
        }
    }
   
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (matrica[i][j] == 1)
                brid(i, j);
        }
    }
    rez = struk(n);
    if (rez == -1)
        cout << "Graf nema ciklusa";
    else
        cout << "Struk zadanog grafa je " << rez;
    getchar();
    getchar();
    return 0;
}