#include <iostream>
#include "tree.h"
#include <cmath>

tree::tree()
{
    isEmpty = true;
}

tree::tree(int item)
{
    root = new_node(item);
    isEmpty = false;
}

tree::~tree()
{
    delete_post_order(root);
}

tree * tree::init(int * array, int size)
{
    tree * t = new tree();
    for (int i = 0; i < size; i++)
        (*t).add(array[i]);
    
    return t;
}

void tree::add(int item)
{
    if (isEmpty) {
        root = new node;
        root->data = item;
        isEmpty = false;
    } else {
        root = insert(root, item);
    }
}

void tree::remove(int item)
{
    if (!contains(item))
        return;
    
    this->root = tproc::remove(this->root, item);
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

bool tree::contains(int item) const
{
    node * temp = root;

    while (temp)
    {
        if (item > temp->data)
            temp = temp->right;
        else if (item < temp->data)
            temp = temp->left;
        else if (item == temp->data)
            return true;
    }

    return false;
}

int tree::findSecondLargest() const
{
    return root->right ? root->right->data : root->data;
}

int tree::findMiddle() const
{
    int min_val = min(root);
    int max_val = max(root);

    int middle_val = (max_val + min_val) / 2;

    if (contains(middle_val)) return middle_val;

    return middle(middle_val, root, root);
}

int middle(int value, node * cur, node * prev)
{
    if (cur)
    {
        int absDiffCur = std::abs(value - cur->data);
        int absDiffPrev = std::abs(value - prev->data);

        if (value > cur->data)
        {
            
            if (!cur->right)    
            {
                return absDiffCur < absDiffPrev ? cur->data
                                                : prev->data; 
            }

            int res = middle(value, cur->right, cur);
            int absDiffRes = std::abs(value - res);
            
            return absDiffCur < absDiffRes ? cur->data
                                           : res;
        }
        else
        {
            if (!cur->left)    
            {
                return absDiffCur < absDiffPrev ? cur->data
                                                : prev->data; 
            }

            int res = middle(value, cur->left, cur);
            int absDiffRes = std::abs(value - res);
            
            return absDiffCur < absDiffRes ? cur->data
                                           : res;
        }
    }

    return 0;
}

node * right_rotation(node * parent)
{
    node * t = parent->left;
    parent->left = t->right;
    t->right = parent;
    fixheight(parent);
    fixheight(t);

    return t;
}

node * left_rotation(node * parent)
{
    node * t = parent->right;
    parent->right = t->left;
    t->left = parent;
    fixheight(parent);
    fixheight(t);

    return t;
}

node * balance(node * n)
{
    fixheight(n);
    int bfact = bfactor(n);

    if(bfact == -2) 
    {
        if(bfactor(n->left) > 0) {
            n->left = left_rotation(n->left);
        }
        return right_rotation(n);
    }
    else if(bfact == 2)
    {
        if(bfactor(n->right) < 0) {
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
    return n ? n->height : - 1;
}

int max_height(node * left, node * right)
{
    int hl = height(left);
    int hr = height(right);

    return (hl > hr ? hl : hr);
}

void fixheight(node * n) {
    n->height = max_height(n->left, n->right) + 1;
}

int bfactor(node * n)
{
    int hr = height(n->right) + 1;
    int hl = height(n->left) + 1;

    return hr - hl;

}

node * new_node(int item)
{
    node * t = new node();  
    t->data = item;
    t->height = 0;
    t->left = t->right = NULL;

    return t;
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


node * findmin(node * root)
{
    node * t = root;

    while (t && t->left != NULL)
        t = t->left;
    return t;
}

node * remove_min(node * root)
{
    if (root->left == NULL)
        return root->right;
    root->left = remove_min(root->left);
    return balance(root);
}

node * tproc::remove(node * root, int item)
{
    if (!root) return NULL;
    if (item > root->data)
        root->right = tproc::remove(root->right, item);
    else if (item < root->data)
        root->left = tproc::remove(root->left, item);
    else
    {
        node * l = root->left;
        node * r = root->right;
        delete root;
        if (!r) return l;
        node * min = findmin(r);
        min->right = remove_min(r);
        min->left = l;

        return balance(min);
    }

    return balance(root);
}

int min(node * root) {
    node * t = root;

    while (t && t->left) { t = t->left; }
    if (!t) return 0;
    return t->data; 
}

int max(node * root) {
    node * t = root;

    while (t && t->right) { t = t->right; }
    if (!t) return 0;
    return t->data;
}