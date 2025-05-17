/*
    Grossi Mara 
*/

#include <iostream>
#include <string.h>
#include "AVL_Node.h"

class AVL_Tree
{
    private:
        AVL_Node* root;

        AVL_Node* insertRec(AVL_Node* node, int new_key, string new_text, AVL_Node* new_parent);
        AVL_Node* findRec(AVL_Node* node, int key_to_find);
        AVL_Node* removeRec(AVL_Node* node, int key_to_remove);
        void showRec(AVL_Node* node);
        void clearRec(AVL_Node* node);

        AVL_Node* leftRotate(AVL_Node* pivot);
        AVL_Node* rightRotate(AVL_Node* pivot);
        int height(AVL_Node* node);
        int getBalance(AVL_Node* node);
        AVL_Node* toBalance(AVL_Node* node, int balancey);
        void Transplant(AVL_Node* x, AVL_Node* y);
        AVL_Node* findMin(AVL_Node* node);

    public:
        AVL_Tree()
        {
            root = nullptr;
        }

        void insert(int new_key, string new_text);
        AVL_Node* find(int key_to_find);
        void remove(int key_to_remove);
        void show();
        void clear();
};


int AVL_Tree::height(AVL_Node* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    else
    {
        return node->height;
    }  
}

//---------------------------------------------------------------------Funzioni per bilanciare l'albero---------------------------------------------------------------------

int AVL_Tree::getBalance(AVL_Node* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    else
    {
        return height(node->left) - height(node->right);
    }
}


AVL_Node* AVL_Tree::toBalance(AVL_Node* node, int balance)
{
    // chiamiamo y il figlio di node con altezza maggiore tra i due e z1, z2 rispettivamente il figlio sx e dx di y

    if(balance > 1 && getBalance(node->left) >= 0)     // caso in cui y è il figlio sx e height(z1) > height(z2)   
    {
        return rightRotate(node);
    }
    else if(balance > 1 && getBalance(node->left) < 0)     // caso in cui y è il figlio sx e height(z1) < height(z2)  
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if(balance < -1 && getBalance(node->right) <= 0)       // caso in cui y è il figlio dx e height(z1) > height(z2)   
    {
        return leftRotate(node);
    }
    else if(balance < -1 && getBalance(node->right) > 0)    // caso in cui y è il figlio dx e height(z1) < height(z2)  
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


AVL_Node* AVL_Tree::leftRotate(AVL_Node* pivot)
{
    AVL_Node* pivot_right = pivot->right;

    pivot->right = pivot_right->left;   

    if(pivot->right != nullptr)
    {
       pivot->right->parent = pivot;
    }

    pivot_right->parent = pivot->parent;

    if(pivot->parent == nullptr)
    {
        root = pivot_right;
    }
    else if(pivot->parent->left == pivot)
    {
        pivot->parent->left = pivot_right;
    }
    else
    {
        pivot->parent->right = pivot_right;
    }

    pivot->parent = pivot_right;
    pivot_right->left = pivot;

    // sistemo le altezze

    pivot->height = 1 + max(height(pivot->left), height(pivot->right));
    pivot_right->height = 1 + max(height(pivot_right->left), height(pivot_right->right));

    return pivot_right;
}


AVL_Node* AVL_Tree::rightRotate(AVL_Node* pivot)
{
    AVL_Node* pivot_left = pivot->left;

    pivot->left = pivot_left->right;  

    if(pivot->left != nullptr)
    {
        pivot->left->parent = pivot;     
    }

    pivot_left->parent = pivot->parent;  
    
    if(pivot->parent == nullptr)
    {
        root = pivot_left;
    }
    else if(pivot->parent->right == pivot)     
    {
        pivot->parent->right = pivot_left;     
    }
    else
    {
        pivot->parent->left = pivot_left;
    }
         
    pivot->parent = pivot_left; 
    pivot_left->right = pivot;  
    
    // sistemo le altezze

    pivot->height = 1 + max(height(pivot->left), height(pivot->right));
    pivot_left->height = 1 + max(height(pivot_left->left), height(pivot_left->right));

    return pivot_left;
}

//---------------------------------------------------------------------Insert---------------------------------------------------------------------

void AVL_Tree::insert(int new_key, string new_text)
{
    root = insertRec(root, new_key, new_text, nullptr);
}


AVL_Node* AVL_Tree::insertRec(AVL_Node* node, int new_key, string new_text, AVL_Node* new_parent)
{
    if (node == nullptr)
    {
        return new AVL_Node(new_key, new_text, new_parent);
    }
    if(new_key > node->key)
    {
        node->right = insertRec(node->right, new_key, new_text, node);
    }
    else
    {
        node->left = insertRec(node->left, new_key, new_text, node);
    }

    // aggiorno l'altezza e sistemo nel caso l'albero si sia sbilanciato

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    return toBalance(node, balance);
}

//---------------------------------------------------------------------Find---------------------------------------------------------------------


AVL_Node* AVL_Tree::find(int key_to_find)
{
    return findRec(root, key_to_find);
}


AVL_Node* AVL_Tree::findRec(AVL_Node* node, int key_to_find)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(node->key == key_to_find)
    {
        return node;
    }
    else if(key_to_find > node->key)
    {
        return findRec(node->right, key_to_find);
    }
    else 
    {
        return findRec(node->left, key_to_find);
    }
}

//---------------------------------------------------------------------Remove---------------------------------------------------------------------

void AVL_Tree::remove(int key_to_remove)
{
    root = removeRec(root, key_to_remove);
}


AVL_Node* AVL_Tree::removeRec(AVL_Node* node, int key_to_remove)
{
    if(node != nullptr)
    {
        if(key_to_remove > node->key)
        {
            node->right = removeRec(node->right, key_to_remove);
        }
        else if(key_to_remove < node->key)
        {
            node->left = removeRec(node->left, key_to_remove);
        }
        else
        {
            if(node->left == nullptr)
            {
               Transplant(node, node->right);
               AVL_Node* temp = node->right;
               free(node);
               return temp;
            }
            else if(node->right == nullptr)
            {
               Transplant(node, node->left);
               AVL_Node* temp = node->left;
               free(node);
               return temp;
            }
            else
            {
                AVL_Node* temp = findMin(node->right); 
                node->key = temp->key;
                node->text = temp->text;
                node->right = removeRec(node->right, temp->key);
            }
        }
    }

    // aggiorno l'altezza e sistemo nel caso l'albero si sia sbilanciato

    if(node != nullptr)
    {
        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);
        return toBalance(node, balance);
    }

    return node;
}


void AVL_Tree::Transplant(AVL_Node* x, AVL_Node* y) 
{
    if(x->parent == nullptr)
    {
        root = y;
    }
    else if(x == x->parent->left)   
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;  
    }
    if(y != nullptr)
    {
        y->parent = x->parent;  
    }
}


AVL_Node* AVL_Tree::findMin(AVL_Node* node)
{
    if(node->left == nullptr)
    {
        return node;
    }
    else
    {
        return findMin(node->left);
    }
}

//---------------------------------------------------------------------Show---------------------------------------------------------------------

void AVL_Tree::show()
{
    showRec(root);
}


void AVL_Tree::showRec(AVL_Node* node)
{
    if(node  != nullptr)
    {
        cout << node->key << ":" << node->text << ":" << node->height << " ";
        showRec(node->left);
        showRec(node->right);
    }
    else
    {
        cout << "NULL ";
    }
}

//---------------------------------------------------------------------Clear---------------------------------------------------------------------

void AVL_Tree::clear()
{
    clearRec(root);
}


void AVL_Tree::clearRec(AVL_Node* node)
{
    clearRec(node->left);
    clearRec(node->right);
}






