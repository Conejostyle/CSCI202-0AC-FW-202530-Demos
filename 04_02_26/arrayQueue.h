#ifndef ARRAYQ_H
#define ARRAYQ_H
#include "queueADT.h"
#include <iostream>

template <class t>
class arrayQueue : public queueADT<t>
{

public:
    arrayQueue(int = queueADT<t>::DEFAULT_QUEUE_SIZE);
    arrayQueue(const arrayQueue<t> &);
    const arrayQueue<t> &operator=(const arrayQueue<t> &);
    ~arrayQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();

private:
    t **list;
    int maxQueueSize;
    int queueFront;
    int queueRear;
    int count;
    void copyQueue(const arrayQueue<t> &);
};

template <class t>
arrayQueue<t>::arrayQueue(int max)
{
    if (max <= 0)
    {
        max = queueADT<t>::DEFAULT_QUEUE_SIZE;
    }
    maxQueueSize = max;
    list = new t *[maxQueueSize];
    for (int i = 0; i < maxQueueSize; i++)
    {
        this->list[i] = nullptr;
    }
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
    count = 0;
}

template <class t>
arrayQueue<t>::arrayQueue(const arrayQueue<t> &otherQueue)
{
    this->list = nullptr;
    this->count = 0;
    this->queueFront = 0;
    this->queueRear = 0;
    copyQueue(otherQueue);
}

template <class t>
const arrayQueue<t> &arrayQueue<t>::operator=(const arrayQueue<t> &otherQueue)
{
    if (this != &otherQueue)
    {
        copyQueue(otherQueue);
    }
    return *this;
}

template <class t>
arrayQueue<t>::~arrayQueue()
{
    initializeQueue();
    delete[] list;
}

template <class t>
bool arrayQueue<t>::isEmptyQueue() const
{
    return queueFront == queueRear || count == 0;
}

template <class t>
bool arrayQueue<t>::isFullQueue() const
{
    return count == maxQueueSize || (queueRear + 1) % maxQueueSize == queueFront;
}

template <class t>
void arrayQueue<t>::initializeQueue()
{
    for (int i = (this->queueFront + 1) % this->maxQueueSize; i != queueRear; i = (i + 1) % this->maxQueueSize)
    {
        delete list[this->queueFront];
        list[this->queueFront] = nullptr;
    }
    this->queueFront = this->maxQueueSize - 1;
    this->queueRear = this->maxQueueSize - 1;
}

template <class t>
t arrayQueue<t>::front() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }

    return *(list[(this->queueFront + 1) % maxQueueSize]);
}

template <class t>
t arrayQueue<t>::back() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(list[queueRear]);
}

template <class t>
void arrayQueue<t>::enqueue(const t &queueElement)
{
    if (isFullQueue())
    {
        throw std::overflow_error("Cannot add to a full queue.");
    }
    /*  else if (queueRear == maxQueueSize)
     {
         std::cout << "Shifting elements" << std::endl;
         for (int i = queueFront; i > 0; i--)
         {
             for (int j = i; j < queueRear; j++)
             {
                 list[j - 1] = list[j];
             }
             queueRear--;
         }
         queueFront = 0;
     } */
    this->queueRear = (this->queueRear + 1) % maxQueueSize;
    list[queueRear] = new t(queueElement);
    count++;
}
template <class t>
t arrayQueue<t>::dequeue()
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot delete from an empty queue.");
    }
    this->queueFront = (queueFront + 1) % maxQueueSize;
    t ret = *(list[this->queueFront]);
    delete list[this->queueFront];
    list[this->queueFront] = nullptr;
    count--;
    return ret;
}
template <class t>
void arrayQueue<t>::copyQueue(const arrayQueue<t> &otherQueue)
{
    this->initializeQueue();
    delete[] this->list;
    this->maxQueueSize = otherQueue.maxQueueSize;
    this->list = new t *[this->maxQueueSize];
    /*  for (int i = 0; i < this->maxQueueSize; i++)
     {
         this->list[i] = nullptr;
     } */
    this->queueFront = otherQueue.queueFront;
    this->queueRear = otherQueue.queueRear;
    /*  for (int i = (this->queueFront + 1) % this->maxQueueSize; i != queueRear; i = (i + 1) % this->maxQueueSize)
     {
         this->list[i] = new t(*(otherQueue.list[i]));
     }
     this->list[this->queueRear] = new t(*otherQueue.list[i]); */
    for (int i = 0; i < this->maxQueueSize; i++)
    {
        if (otherQueue.list[i] != nullptr)
        {
            this->list[i] = new t(*(otherQueue.list[i]));
        }
        else
        {
            this->list[i] = nullptr;
        }
    }
}
#endif