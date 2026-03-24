#ifndef LINKED_H
#define LINKED_H

template <class t>
class linkedListType
{
public:
    linkedListType();
    linkedListType(const linkedListType<t> &otherList);
    const linkedListType<t> &operator=(const linkedListType<t> &);
    ~linkedListType();
    void destroyList();
    bool isEmptyList() const;
    int length() const;
    t front() const;
    t back() const;
    virtual void insert(const t &newInfo) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;
    virtual bool search(const t &searchItem) const = 0;
    void print(std::ostream &, std::string = " ") const;

protected:
    node<t> *head;
    node<t> *tail;
    int count;

private:
    void copyList(const linkedListType<t> &otherList);
};

template <class t>
linkedListType<t>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

#endif