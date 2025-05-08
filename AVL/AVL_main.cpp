#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include "AVL_Tree.h"
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

int main()
{
    AVL_Tree* tree = new AVL_Tree();

    vector<string> operation;

    while(cin >> operation)
    {
        if(operation[0] == "insert")
        {
            tree->insert(stoi(operation[1]), operation[2]);
        }
        else if(operation[0] == "find")
        {
            AVL_Node* result = tree->find(stoi(operation[1]));
            cout << (result != nullptr ? result->text : "NULL") << endl;
        }
        else if(operation[0] == "remove")
        {
            tree->remove(stoi(operation[1]));
        }
        else if(operation[0] == "show")
        {
            tree->show();
            cout << endl;
        }
        else if(operation[0] == "clear")
        {
            tree->clear();
        }
        else
        {
            return 1;
        }

        operation.clear();
    }

    return 0;
}