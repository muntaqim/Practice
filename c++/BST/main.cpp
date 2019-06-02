#include "BST.h"
#include "Node.h"

int main(void)
{
    vector<int> a{10,3,5,3,6,2,4};
    BST<int> bst(a);
    bst.printInorder();
}
