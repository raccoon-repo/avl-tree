#include <iostream>
#include <cstdlib>
#include "tree.h"

int main()
{
    int values[] = {8, 13, 19, 10, 16, 14, 22, 31, 32, 26, 30}; 

    tree * t = tree::init(values, 11);
    std::cout << (*t).findMiddle() << std::endl; // 19

    return 0;
}
