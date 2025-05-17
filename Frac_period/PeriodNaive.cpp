/*
    Grossi Mara 
*/

#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

istream &operator >> (istream &in, vector<string> &vec) 
{
    string line;
    getline(in, line);

    istringstream is(line);
    
    string value;
    while (is >> value)
    {
        vec.push_back(value);
    }  

    return in;
}

int periodNaive(string s);

int main()
{
    string s;
    cin >> s;

    cout << periodNaive(s) << endl;

    return 0;
}


int periodNaive(string s)
{
    int lenght = s.length();
    string s1, s2;

    for(int p = 1; p <= lenght - 1; p++)
    {
        s1 = s.substr(0, lenght - p);
        s2 = s.substr(p, lenght);

        if(s1 == s2)
        {
            return p;
        }
    }

    return lenght;
}