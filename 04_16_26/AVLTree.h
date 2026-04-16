#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>
#include <iostream>

template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    AVLTree(int (*comp)(const t &, const t &) = cmp);
    void insert(const t &insertItem);
    void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(binaryNode<t> *currentNode);
        bool hasNext();
        t next();
        Iterator operator++();
        t &operator*();

    private:
        linkedStack<binaryNode<t> *> nodeStack;
        void pushLeftNodes(binaryNode<t> *node);
    };
    Iterator begin() { return Iterator(this->root); };
    Iterator end() { return Iterator(nullptr); };
    Iterator find(const t &searchItem) const;
    bool isBalanced();

private:
    void balanceFromLeft(binaryNode<t> *&currentNode);
    void balanceFromRight(binaryNode<t> *&currentNode);
    void rotateToLeft(binaryNode<t> *&currentNode);
    void rotateToRight(binaryNode<t> *&currentNode);
    void insertIntoAVL(binaryNode<t> *&currentNode, binaryNode<t> *newNode, bool &isTaller);
    Iterator find(const t &searchItem, binaryNode<t> *currentNode) const;
    int calculateBalance(binaryNode<t> *currentNode);
    bool isBalanced(binaryNode<t> *currentNode);
    void balanceTree(binaryNode<t> *&u);
    void deleteFronTree(binaryNode<t> *&u, const t &key);
    binaryNode<t> *findMin(binaryNode<t> *node) const;
};

#endif