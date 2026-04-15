#include "binarySearchTree.h"
#include <iostream>
#include <random>

// M05 part A lab
// run the program 3 times, and use preorder traversal to draw the shape of the tree.

int main()
{
    binarySearchTree<int> tree;
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator(time(0));
    int num = distribution(generator);
    for (int i = 0; i < num; i++)
    {
        try
        {
            tree.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << tree.inorderTraversal() << std::endl;
    std::cout << tree.preorderTraversal() << std::endl;
    std::cout << tree.postorderTraversal() << std::endl;
    std::cout << "Generated num: " << num << std::endl;
    std::cout << "Tree Height: " << tree.treeHeight() << std::endl;
    std::cout << "Tree Nodes: " << tree.treeNodeCount() << std::endl;
    std::cout << "Tree Leaves: " << tree.treeLeavesCount() << std::endl;
}