#ifndef _BALANCED_BINARY_SEARCH_TREE_
#define _BALANCED_BINARY_SEARCH_TREE_

typedef struct node {
    int data;
    int height;
    node * right;
    node * left;
} tree_node;

class tree {
private:
    node * root;
    bool isEmpty;
public:
    tree();
    tree(int item);
    ~tree();

    void add(int);
    void remove(int);

    void inorder() const;
    void preorder() const;
    void postorder() const;
    bool contains() const;
};

node * insert(node * root, int item);
node * new_node(int item);
node * right_rotation(node * root);
node * left_rotation(node * root);
node * balance(node * root);

void fixheight(node * root);
void inorder_traversal(node * root);
void preorder_traversal(node * root);
void postorder_traversal(node * root);
void delete_post_order(node * root);

int bfactor(node * root);


#endif