#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
int cmp(const t &item1, const t &item2)
{
    if (item1 > item2)
    {
        return 1;
    }
    if (item1 == item2)
    {
        return 0;
    }
    if (item1 < item2)
    {
        return -1;
    }
}

template <class t>
class binarySearchTree : public binaryTreeType<t>
{
public:
    binarySearchTree(int (*comp)(const t &, const t &) = cmp);
    void insert(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);

private:
    int (*compare)(const t &item1, const t &item2);
    void deleteFromTree(const t &searchItem, binaryNode<t> *currentNode);
    bool search(const t &searchItem, binaryNode<t> *currentNode);
    void insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode);
};

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}
template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insert(newNode, this->getRoot());
}
template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->root);
}
template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int compareValue = compare(searchItem, *currentNode->data);
    if (compareValue == 0)
    {
        return true;
    }
    if (compareValue == -1)
    {
        return search(searchItem, currentNode->lLink);
    }
    else
    {
        return search(searchItem, currentNode->rLink);
    }
}
template <class t>
void binarySearchTree<t>::insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int compareValue = compare(*insertItem->data, *currentNode->data);
        if (compareValue == 0)
        {
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed");
        }
        if (compareValue == -1)
        {
            insert(insertItem, currentNode->lLink);
        }
        else
        {
            insert(insertItem, currentNode->rLink);
        }
    }
}
#endif