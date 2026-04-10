#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include "unorderedLinkedList.h"

template <class t>
linkedListIterator<t> seqSearch(unorderedLinkedList<t> &list, const t &item, int &count)
{
    count = 0;
    bool found = false;
    linkedListIterator<t> itRet;
    for (linkedListIterator<t> it = list.begin(); it != list.end() && !found; ++it)
    {
        count++;
        if (*(*it) == item) //(*it) gives us a t *
        {
            found = true;
            itRet = it;
        }
    }

    return itRet;
}

template <class t>
int binarySearch(const t list[], int length, const t &item, int &comp, int first, int last)
{
    if (last < first)
    {
        return -1;
    }
    int mid = 0;
    mid = (first + last) / 2;
    comp++;
    if (list[mid] == item)
    {
        return mid;
    }
    if (list[mid] > item)
    {
        return binarySearch(list, length, item, comp, first, mid - 1);
    }
    if (list[mid] < item)
    {
        return binarySearch(list, length, item, comp, mid + 1, last);
    }
    return -1;
}

// =========== Sort Algorithms ==============

template <class t>
void bubbleSort(unorderedLinkedList<t> &list)
{

    for (int iteration = 1; iteration < list.length(); iteration++)
    {
        linkedListIterator<t> it1;
        for (linkedListIterator<t> it = it1 = list.begin(); ++it1 != list.end(); ++it)
        {

            if (*(*it) > *(*it1))
            {
                swap(it, it1);
            }
        }
    }
}

template <class t>
void swap(linkedListIterator<t> &first, linkedListIterator<t> &second)
{
    t *temp = *first;
    *first = *second;
    *second = temp;
}
template <class t>
linkedListIterator<t> findSmallest(unorderedLinkedList<t> &list, linkedListIterator<t> &begin)
{
    t smallest = *(*begin);
    linkedListIterator<t> ret = begin;
    linkedListIterator<t> it = begin;
    for (++it; it != list.end(); ++it)
    {
        if (*(*it) < smallest)
        {
            smallest = *(*it);
            ret = it;
        }
    }
    return ret;
}

template <class t>
void selectionSort(unorderedLinkedList<t> &list)
{
    linkedListIterator<t> unsort = list.begin();
    int i = 1;
    for (unsort; unsort != list.end(); ++unsort)
    {
        linkedListIterator<t> smallest = findSmallest(list, unsort);
        if (smallest != unsort)
        {
            swap(unsort, smallest);
        }
        i++;
    }
}

template <class t>
void insertionSort(t list[], int length)
{
    for (int firstOutOfOrder = 1; firstOutOfOrder < length; ++firstOutOfOrder)
    {
        if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
        {
            t temp = list[firstOutOfOrder];
            int location = firstOutOfOrder;
            do
            {
                list[location] = list[location - 1];
                location--;
            } while (location > 0 && list[location - 1] > temp);
            list[location] = temp;
        }
    }
}

template <class t>
int partition(t list[], int low, int high, int (*comp)(t &, t &))
{
    t pivot = list[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        t item = list[j];
        if (comp(item, pivot) < 0)
        {
            i++;
            list[j] = list[i];
            list[i] = item;
        }
    }
    i++;
    t temp = list[i];
    list[i] = list[high];
    list[high] = temp;
    return i;
}

template <class t>
void quickSort(t list[], int low, int high, int (*comp)(t &, t &))
{
    if (low < high)
    {
        int pi = partition(list, low, high, comp);
        quickSort(list, low, pi - 1, comp);
        quickSort(list, pi + 1, high, comp);
    }
}

template <class t>
void merge(t array[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    t *leftArray = new t[leftSize];
    t *rightArray = new t[rightSize];
    for (int i = 0; i < leftSize; i++)
    {
        leftArray[i] = array[left + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArray[i] = array[mid + 1 + i];
    }
    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = left;
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftArray[leftIndex] <= rightArray[rightIndex])
        {
            array[mergeIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else
        {
            array[mergeIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergeIndex++;
    }
    while (leftIndex < leftSize)
    {
        array[mergeIndex++] = leftArray[leftIndex++];
    }
    while (rightIndex < rightSize)
    {
        array[mergeIndex++] = rightArray[rightIndex++];
    }
    delete[] leftArray;
    delete[] rightArray;
}

template <class t>
void mergeSort(t array[], int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

#endif