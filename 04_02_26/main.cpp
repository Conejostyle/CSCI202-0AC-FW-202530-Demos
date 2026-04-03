#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "process.h"
#include "arrayQueue.h"
#include "linkedQueue.h"
#include "unorderedLinkedList.h"

void printMenu();
void processFile(linkedQueue<process> &ready, arrayQueue<process> &waiting, int &processCount);
int getMenuChoice();
void resetStream();
void processChoice(int choice, linkedQueue<process> &, arrayQueue<process> &, unorderedLinkedList<process> &);
void runNextProcess(linkedQueue<process> &ready, arrayQueue<process> &waiting, unorderedLinkedList<process> &finished);
void interrupt(linkedQueue<process> &ready, arrayQueue<process> &waiting);
void listProcesses(linkedQueue<process> &, arrayQueue<process> &, unorderedLinkedList<process> &);

int main()
{
    unorderedLinkedList<process> finished;
    linkedQueue<process> ready;
    arrayQueue<process> waiting;
    int processCount = 0;
    processFile(ready, waiting, processCount);
    // int i = 1;
    std::cout << std::setfill('-');
    int choice = 0;
    while (choice != 4)
    {

        if (processCount == finished.length())
        {
            choice = 4;
            std::cout << "All processes have finished. Shutting Down." << std::endl;
        }
        else
        {
            choice = getMenuChoice();
        }
        processChoice(choice, ready, waiting, finished);
    }

    return 0;
}

void printMenu()
{
    std::cout << "Please choose from the following menu: " << std::endl;
    std::cout << "1. Run Next Process" << std::endl;
    std::cout << "2. Trigger an Interrupt" << std::endl;
    std::cout << "3. List All Processes" << std::endl;
    std::cout << "4. Shut Down" << std::endl;
    std::cout << "Your Choice: ";
}

void processFile(linkedQueue<process> &ready, arrayQueue<process> &waiting, int &processCount)
{
    std::ifstream in;
    in.open("processes.txt");
    processCount = 0;
    while (!in.eof() && in.is_open())
    {
        std::string name;
        int priority;
        int slicesNeeded;
        int IOSlice;
        std::string statusStr;
        in >> name >> priority >> slicesNeeded >> IOSlice >> statusStr;
        if (!in)
        {
            break;
        }
        std::transform(statusStr.begin(), statusStr.end(), statusStr.begin(), ::tolower);
        process p(name, priority, slicesNeeded, IOSlice, strToStatus.at(statusStr));
        processCount++;
        if (p.getStatus() == WAITING)
        {
            waiting.enqueue(p);
        }
        else
        {
            ready.enqueue(p);
        }
    }
}

int getMenuChoice()
{
    int choice;
    std::cout << std::endl;
    printMenu();
    std::cin >> choice;
    while (!std::cin || choice < 1 || choice > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid choice." << std::endl;
        printMenu();
        std::cin >> choice;
    }
    return choice;
}

void processChoice(int choice, linkedQueue<process> &ready, arrayQueue<process> &waiting, unorderedLinkedList<process> &finished)
{
    switch (choice)
    {
    case 1:

        runNextProcess(ready, waiting, finished);

        break;

    case 2:
        interrupt(ready, waiting);
        break;
    case 3:
        listProcesses(ready, waiting, finished);
        break;
    case 4:
        std::cout << "Shuttng Down:" << std::endl;
        listProcesses(ready, waiting, finished);
        break;
    }
}

void runNextProcess(linkedQueue<process> &ready, arrayQueue<process> &waiting, unorderedLinkedList<process> &finished)
{
    try
    {

        process p(ready.dequeue());
        std::cout << "Running Process:" << std::endl;
        std::cout << p << std::endl;
        p.run();
        if (p.getStatus() == WAITING)
        {
            waiting.enqueue(p);
        }
        else if (p.getStatus() == READY)
        {
            ready.enqueue(p);
        }
        else
        {
            finished.insert(p);
        }
    }
    catch (...)
    {
        std::cout << "There are no ready processes. Try to do an interrupt." << std::endl;
    }
}

void interrupt(linkedQueue<process> &ready, arrayQueue<process> &waiting)
{
    try
    {
        process p(waiting.dequeue());
        p.changeStatus(READY);
        std::cout << "Moving process to Ready:" << std::endl;
        std::cout << p << std::endl;
        ready.enqueue(p);
    }
    catch (...)
    {
        std::cout << "No Waiting Processes." << std::endl;
    }
}

void listProcesses(linkedQueue<process> &ready, arrayQueue<process> &waiting, unorderedLinkedList<process> &finished)
{
    linkedQueue readyTemp(ready);
    arrayQueue waitingTemp(waiting);
    std::cout << "List of Ready Processes: " << std::endl;
    while (!readyTemp.isEmptyQueue())
    {
        std::cout << std::setw(40) << "-" << std::endl;
        std::cout << readyTemp.dequeue() << std::endl;
        std::cout << std::setw(40) << "-" << std::endl;
    }
    std::cout << "List of Waiting Processes: " << std::endl;
    while (!waitingTemp.isEmptyQueue())
    {
        std::cout << std::setw(40) << "-" << std::endl;
        std::cout << waitingTemp.dequeue() << std::endl;
        std::cout << std::setw(40) << "-" << std::endl;
    }
    std::cout << "List of Finished Processes: " << std::endl;
    finished.print(std::cout, "\n");
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}
