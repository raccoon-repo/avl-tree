#include <iostream>
#include <cstdlib>
#include "tree.h"

int main()
{
    tree tree1 = tree();

    tree1.add(8);
    tree1.add(9);
    tree1.add(1);
    tree1.add(3);
    tree1.add(11);
    tree1.add(2);
    tree1.add(20);
    tree1.add(21);

    tree1.postorder(); // 1-3-2-9-21-20-11-8

    return 0;
}
