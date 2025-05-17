/*
    Grossi Mara 
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
using namespace std;

class Node
{
    public:
        int key;
        Node* right;
        Node* left;
        Node* parent;

    Node(int new_key, Node* new_left, Node* new_right)
    {
        this->key = new_key;
        this->left = new_left;
        this->right = new_right;

        if(this->left != nullptr)
        {
            this->left->parent = this;
        }
        if(this->right != nullptr)
        {
            this->right->parent = this;
        }
    }
};

struct results
{
    Node* node;
    int pos;
};

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

bool isBST(Node* root, size_t size);
int inOrder(Node* root, int* tree_array, int index);
results decodeTree(vector<string> tree_elements, int index);

int main()
{
    vector<string> tree_elements;
    cin >> tree_elements;

    results root = decodeTree(tree_elements, 0);
    
    cout << isBST(root.node, tree_elements.size()) << endl;

    return 0;
}


results decodeTree(vector<string> tree_elements, int index)
{
    if(tree_elements.at(index) == "NULL")
    {
        return results{nullptr, index + 1};
    }

    int key = stoi(tree_elements.at(index));
    results left_child = decodeTree(tree_elements, index + 1);
    results right_child = decodeTree(tree_elements, left_child.pos);

    return results{new Node(key, left_child.node, right_child.node), right_child.pos};
}


int inOrder(Node* node, int* tree_array, int index)
{
    if(node != nullptr)
    {
        int new_index = inOrder(node->left, tree_array, index);
        tree_array[new_index] = node->key;
        return inOrder(node->right, tree_array, new_index + 1);
    }

    return index;
}


bool isBST(Node* root, size_t size)
{
    int* tree_array = (int*) malloc(sizeof(int) * size);

    int actual_size = inOrder(root, tree_array, 0);

    for(int i = 1; i < actual_size; i++)
    {
        if(tree_array[i] < tree_array[i - 1])
        {
            return 0;
        }
    }

    return 1;
}


