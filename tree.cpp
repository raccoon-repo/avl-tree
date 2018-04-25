#include <iostream>
#include "tree.h"

tree::tree()
{
    isEmpty = true;
}

tree::tree(int item)
{
    this->root = new_node(item);
    isEmpty = false;
}

tree::~tree()
{
    delete_post_order(root);
}

void tree::add(int item)
{
    insert(this->root, item);
}

void tree::remove(int item)
{

}

void tree::inorder() const
{
    inorder_traversal(root);
}

void tree::postorder() const
{
    postorder_traversal(root);
}

void tree::preorder() const
{
    preorder_traversal(root);
}

bool tree::contains() const
{
    return false;
}

node * right_rotation(node * parent)
{
    node * t = parent->left;
    parent->left = t->right;
    t->right = parent;
    fixheight(t);
    fixheight(parent);

    return t;
}

node * left_rotation(node * parent)
{
    node * t = parent->right;
    parent->right = t->left;
    t->left = parent;
    fixheight(t);
    fixheight(parent);

    return t;
}

node * balance(node * n)
{
    fixheight(n);
    int bfact = bfactor(n);

    if(bfact == 2) 
    {
        if(bfactor(n->left) < 0) {
            n->left = left_rotation(n->left);
        }
        return right_rotation(n);
    }
    else if(bfact == -2)
    {
        if(bfactor(n->right) > 0) {
            n->right = right_rotation(n->right);
        }
        return left_rotation(n);
    }

    return n; 

}

node * insert(node * n, int item)
{
    if(!n) {
        n = new_node(item);
        return n;
    }

    if (item > n->data) {
        n->right = insert(n->right, item);
    } else if (item < n->data) {
        n->left = insert(n->left, item);
    }

    return balance(n);
}

int height(node * n) 
{
    return n ? n->height : 0;
}

int max_height(node * left, node * right)
{
    int hl = height(left);
    int hr = height(right);

    return (hl > hr ? hl : hr);
}

void fixheight(node * n) {
    n->height = max_height(n->left, n->right);
}

int bfactor(node * n)
{
    return height(n->left) - height(n->right);
}

node * new_node(int item)
{
    node * t = new node();
    t->data = item;
    t->height = 0;
}

void inorder_traversal(node * root) 
{
    if (root == NULL)
        return;

    inorder_traversal(root->left);
    std::cout << root->data << " ";
    inorder_traversal(root->right);
}

void postorder_traversal(node * root) 
{
    if (root == NULL)
        return;
    
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    std::cout << root->data << " ";

}

void preorder_traversal(node * root)
{
    if (root == NULL)
        return;
    
    std::cout << root->data << " ";
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void delete_post_order(node * root)
{
    if (!root)
        return;
    
    delete_post_order(root->left);
    delete_post_order(root->right);
    delete root;
}