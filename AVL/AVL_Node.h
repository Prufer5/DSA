#include <iostream> 
using namespace std;

class AVL_Node
{
    public:
        int key;
        string text;
        int height;
        AVL_Node* left;
        AVL_Node* right;
        AVL_Node* parent;


    AVL_Node(int new_key, string new_text, AVL_Node* new_parent)
    {
        this->key = new_key;
        this->text = new_text;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = new_parent;
    }
};