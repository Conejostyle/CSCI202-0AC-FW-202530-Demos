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

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : binarySearchTree(comp)
{
}

template <class t>
void AVLTree<t>::insert(const t &insertItem)
{
    bool isTaller = false;
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->bfactor = 0;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insertIntoAVL(this->root, newNode, isTaller);
}

template <class t>
void AVLTree<t>::balanceFromLeft(binaryNode<t> *&currentNode)
{
    binaryNode *lChild;
    binaryNode<t> *lChild_RChild;
    lChild = currentNode->lLink;
    switch (lChild->bfactor)
    {
    case 0:
    case -1: // case 1 left child of current node is left high
        currentNode->bfactor = 0;
        lChild->bfactor = 0;
        rotateToRight(currentNode);
        break;
    case 1:
        lChild_RChild = lChild->rLink;
        switch (lChild_RChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 1;
            lChild->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = 0;
            lChild->bfactor = -1;
            break;
        }
        lChild_RChild->bfactor = 0;
        rotateToLeft(currentNode->lLink);
        rotateToRight(currentNode);
        break;
    }
}

template <class t>
inline void AVLTree<t>::balanceFromRight(binaryNode<t> *&currentNode)
{
    binaryNode *rChild;
    binaryNode<t> *rChild_LChild;
    rChild = currentNode->rLink;
    switch (rChild->bfactor)
    {

    case -1: // case 1 left child of current node is left high
        rChild_LChild = rChild->lLink;
        switch (rChild_LChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rChild->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rChild->bfactor = 0;
            break;
        }
        rChild_LChild->bfactor = 0;
        rotateToRight(currentNode->rLink);
        rotateToLeft(currentNode);
        break;

    case 0:
    case 1:
        currentNode->bfactor = 0;
        rChild->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::insertIntoAVL(binaryNode<t> *&currentNode, binaryNode<t> *newNode, bool &isTaller)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
    }
    else
    {
        int compareValue = this->compare(**newNode, **currentNode); // ** dereferences the node pointer and with the * operator overload gives us the data.
        if (compareValue == 0)
        {
            throw std::invalid_argument("No Duplicates Allowed");
        }
        else if (compareValue == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                }
            }
        }
    }
}

#endif