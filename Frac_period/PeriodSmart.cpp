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

int periodSmart(string s);

int main()
{
    string s;
    cin >> s;

    cout << periodSmart(s) << endl;

    return 0;
}


int periodSmart(string s)
{
    int string_length = s.length();   
    int max_edges_lengths[string_length];

    max_edges_lengths[0] = -1;

    int current_max_edge;

    for(int p = 0; p <  string_length - 1; p++)
    {
        current_max_edge = max_edges_lengths[p];

        while(current_max_edge >= 0 && (s[current_max_edge + 1] != s[p + 1]))
        {
            current_max_edge = max_edges_lengths[current_max_edge];
        }

        if(s[current_max_edge + 1] == s[p + 1])
        {
            max_edges_lengths[p + 1] = current_max_edge + 1;
        }
        else
        {
            max_edges_lengths[p + 1] = -1;
        }
    }

    return string_length - (max_edges_lengths[string_length - 1] + 1);
}


