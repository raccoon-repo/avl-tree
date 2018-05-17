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
    bool contains(int item) const;

    int findSecondLargest() const;
    int findMiddle() const;

    static tree * init(int * array, int size);
};

node * new_node(int item);

node * insert(node * root, int item);
node * right_rotation(node * root);
node * left_rotation(node * root);
node * balance(node * root);
node * findmin(node * root);
node * remove_min(node * root);

int middle(int value, node * cur, node * prev);
int max(node * root);
int min(node * root);

namespace tproc {
    int findSecondLargest(node * root);
    node * remove(node * root, int item);
}

void fixheight(node * root);

void inorder_traversal(node * root);
void preorder_traversal(node * root);
void postorder_traversal(node * root);
void delete_post_order(node * root);

int bfactor(node * root);


#endif
