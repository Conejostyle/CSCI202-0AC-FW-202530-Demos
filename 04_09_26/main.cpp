#include <iostream>
#include <random>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include "unorderedLinkedList.h"
#include "searchSort.h"
#include "person.h"

void setup();

int compareByName(Person *&, Person *&);
int compareByAge(Person *&, Person *&);
int compareByHeight(Person *&, Person *&);
void printPeopleList(Person **, int);

int main()
{
    unorderedLinkedList<int> list;
    unorderedLinkedList<int> bList;
    unorderedLinkedList<int> sList;
    int iList[1000000];
    std::ifstream in("input.txt");
    int i = 0;
    while (!in.eof())
    {
        int x;
        in >> x;
        list.insert(x);
        iList[i++] = x;
    }
    bList = list;
    sList = list;
    int searchTerm = 517717;
    int count = 0;
    linkedListIterator<int> it = seqSearch(list, searchTerm, count);
    if (it == list.end())
    {
        std::cout << "The item was not found in the list" << std::endl;
    }
    else
    {
        std::cout << *(*it) << " is in the list on line " << count << std::endl;
    }
    // bubbleSort(bList);
    // selectionSort(sList);
    // insertionSort(iList, 1000000);
    mergeSort(iList, 0, 1000000);
    list.mergeSort();
    std::cout << "Merge Sort Finished" << std::endl;

    Person **people = new Person *[10];
    people[0] = new Person("Brian Busch", 32, 168);
    people[1] = new Person("Amber Hammond", 49, 155);
    people[2] = new Person("Jason Buckles", 28, 182);
    people[3] = new Person("Richard Asbury", 42, 182);
    people[4] = new Person("Rebecca Rivera", 69, 174);
    people[5] = new Person("Nikia Shurtleff", 51, 163);
    people[6] = new Person("Derek Hancock", 29, 168);
    people[7] = new Person("Elias Gomez", 47, 184);
    people[8] = new Person("Timothy Michael", 49, 170);
    people[9] = new Person("Bernard McElroy", 60, 183);

    quickSort(people, 0, 9, compareByName);
    std::cout << "sorted by name" << std::endl;
    printPeopleList(people, 10);
    std::cout << std::endl;
    quickSort(people, 0, 9, compareByAge);
    std::cout << "Sorted by age" << std::endl;
    printPeopleList(people, 10);
    std::cout << std::endl;
    quickSort(people, 0, 9, compareByHeight);
    std::cout << "Sorted by Height" << std::endl;
    printPeopleList(people, 10);
    std::cout << std::endl;

    // setup();
    return 0;
}

void setup()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1, 2000000);
    std::unordered_set<int> nums;
    std::ofstream out("input.txt");
    while (nums.size() != 1000000)
    {
        nums.insert(distribution(generator));
    }
    for (auto it = nums.begin(); it != nums.end(); ++it)
    {
        out << *it << std::endl;
    }
}

int compareByName(Person *&person1, Person *&person2)
{
    if (person1->getName() > person2->getName())
    {
        return 1;
    }
    else if (person1->getName() == person2->getName())
    {
        return 0;
    }
    else if (person1->getName() < person2->getName())
    {
        return -1;
    }
    return 0;
}

int compareByAge(Person *&person1, Person *&person2)
{
    if (person1->getAge() > person2->getAge())
    {
        return 1;
    }
    else if (person1->getAge() == person2->getAge())
    {
        return 0;
    }
    else if (person1->getAge() < person2->getAge())
    {
        return -1;
    }
    return 0;
}

int compareByHeight(Person *&person1, Person *&person2)
{
    if (person1->getHeight() > person2->getHeight())
    {
        return 1;
    }
    else if (person1->getHeight() == person2->getHeight())
    {
        return 0;
    }
    else if (person1->getHeight() < person2->getHeight())
    {
        return -1;
    }
    return 0;
}

void printPeopleList(Person **p, int num)
{
    for (int i = 0; i < num; i++)
    {
        std::cout << *p[i] << std::endl;
    }
}
