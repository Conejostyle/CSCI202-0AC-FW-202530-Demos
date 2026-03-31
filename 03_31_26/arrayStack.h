#ifndef ASTACK_H
#define ASTACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class arrayStack : public stackADT<t>
{
public:
    arrayStack(int = stackADT::DEFAULT_STACK_SIZE);
    arrayStack(const arrayStack<t> &);
    const arrayStack<t> &operator=(const arrayStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t top() const;
    t pop();
    ~arrayStack();

private:
    void copyStack(const arrayStack<t> &);
    t getTopItem() const;
    int stackTop;
    int maxStackSize;
    t **list;
};

#endif