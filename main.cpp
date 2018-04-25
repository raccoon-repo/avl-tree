#include <iostream>
#include <cstdlib>
#include "tree.h"

int main()
{
    tree * tree1 = new tree();

    (*tree1).add(8);
    (*tree1).add(9);
    (*tree1).add(1);
    (*tree1).add(3);
    (*tree1).add(11);
    (*tree1).add(2);
    (*tree1).add(20);
    (*tree1).add(21);

    (*tree1).postorder();

    delete tree1;
    return 0;
}
