#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack(int = stackADT::DEFAULT_STACK_SIZE);
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t top() const;
    t pop();
    ~linkedStack();

private:
    void copyStack(const linkedStack<t> &);
    t getTopItem() const;
    node<t> *stackTop;
    int count;
};

#endif