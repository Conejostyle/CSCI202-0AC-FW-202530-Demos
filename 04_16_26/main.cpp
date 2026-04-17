#include "binarySearchTree.h"
#include "AVLTree.h"

#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

// M05 part b lab
//  create a node for a b-tree.

int main()
{
    binarySearchTree<int> tree3;
    AVLTree<int> tree;
    std::uniform_int_distribution<int> distribution(5, 100);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    int num = distribution(generator);
    AVLTree<int> tree2;
    std::ofstream out("out.txt");
    for (int i = 0; i < num; i++)
    {
        try
        {
            int value = distribution(generator);
            tree3.insert(value);
            tree.insert(value);
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
    out << tree.inorderTraversal() << std::endl;
    out.close();
    std::ifstream in("out.txt");
    while (!in.eof())
    {
        int x;
        in >> x;
        if (!in)
            break;
        tree2.insert(x);
    }
    std::cout << tree2.inorderTraversal() << std::endl;
    std::cout << tree2.preorderTraversal() << std::endl;
    std::cout << tree2.postorderTraversal() << std::endl;
}
