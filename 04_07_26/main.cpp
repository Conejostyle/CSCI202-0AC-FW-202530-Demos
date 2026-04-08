#include <iostream>
#include <string>
#include <limits>
#include "linkedStack.h"

const int DEFAULT = 0;
void resetStream();
int factorial(int n);

int inputInt(std::string prompt, std::string error, bool (*valid)(int, int, int), int lower = 0, int upper = 0);
bool intInRange(int n, int lower, int upper);
bool intGTX(int n, int x, int = DEFAULT);
bool intLTX(int n, int x, int = DEFAULT);
bool intGTEQ(int n, int x, int = DEFAULT);
bool intLTEQ(int n, int x, int = DEFAULT);
long fibNum(long f[], long n);

void moveDisks(int, char source, char destination, char spare);
void moveDisks(int disk, linkedStack<int> &source, linkedStack<int> &destination, linkedStack<int> &spare, char s, char d, char sp);

// M04 part A lab
// use the fibonacci number code from page 296 of the textbook
// implement as a function
// compare with recursive version
// which do you prefer and why?
// submit your preference and the function

int main()
{
    std::string prompt = "Enter a number greater than 0: ";
    std::string err = "Please enter a number greater than 0.";
    int n = inputInt(prompt, err, intGTX, -1);
    std::cout << factorial(n) << std::endl;
    prompt = "Enter the first fibonacci number: ";
    err = "The number entered must be greater than 0.";
    long fibNum1 = inputInt(prompt, err, intGTX);
    prompt = "Enter the second fibonacci number: ";
    err = "The number entered must be greater than or equal to " + std::to_string(fibNum1);
    long fibNum2 = inputInt(prompt, err, intGTEQ, fibNum1);
    prompt = "Enter the position of the desired fibonacci number: ";
    err = "The number entered must be greater than 0.";
    long nthFibonacci = inputInt(prompt, err, intGTX);
    long *fibSeq = new long[nthFibonacci];
    for (int i = 0; i < nthFibonacci; i++)
    {
        fibSeq[i] = -1;
    }
    fibSeq[0] = fibNum1;
    fibSeq[1] = fibNum2;

    std::cout << "The " << nthFibonacci << "th Fibonacci number is " << fibNum(fibSeq, nthFibonacci) << std::endl;

    moveDisks(4, '1', '3', '2');
    std::cout << std::endl
              << std::endl;
    linkedStack<int> source;
    linkedStack<int> destination;
    linkedStack<int> spare;
    for (int i = 4; i > 0; i--)
    {
        source.push(i);
    }
    moveDisks(4, source, destination, spare, '1', '3', '2');

    return 0;
}

int factorial(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    return n * factorial(n - 1); // n! = n * (n-1)!
}
void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int inputInt(std::string prompt, std::string error, bool (*valid)(int, int, int), int lower, int upper)
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    if (std::cin && valid(num, lower, upper))
    {
        return num;
    }
    if (!std::cin)
    {
        resetStream();
    }
    std::cout << error << std::endl;
    return inputInt(prompt, error, valid, lower, upper);

    /*  if (!std::cin)
     {
         resetStream();
         std::cout << error << std::endl;
         return inputInt(prompt, error, valid, lower, upper);
     }
     if (!valid(num, lower, upper))
     {
         std::cout << error << std::endl;
         return inputInt(prompt, error, valid, lower, upper);
     } */

    /* if (std::cin && valid(num, lower, upper))
    {
        return num;
    }
    else
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << error << std::endl;
        return inputInt(prompt, error, valid, lower, upper);
    } */

    // return num;
}

bool intInRange(int n, int lower, int upper)
{

    return lower <= n && n <= upper;
}

bool intGTX(int n, int x, int)
{
    return n > x;
}

/* int factorial(int n)
{
    int f = 1;
    for (int i = 1; i <= n; i++)
    {
        f *= i;
    }
    return f;
} */

bool intLTX(int n, int x, int)
{
    return n < x;
}

bool intGTEQ(int n, int x, int)
{
    return n >= x;
}

bool intLTEQ(int n, int x, int)
{
    return n <= x;
}

long fibNum(long f[], long n)
{
    if (n <= 0)
    {
        return 0;
    }
    if (f[n - 1] != -1)
    {
        return f[n - 1];
    }
    f[n - 1] = fibNum(f, n - 1) + fibNum(f, n - 2);
    return f[n - 1];
}

void moveDisks(int count, char source, char destination, char spare)
{
    if (count > 0)
    {
        moveDisks(count - 1, source, spare, destination);
        std::cout << "Move disk " << count << " from " << source << " to " << destination << std::endl;
        moveDisks(count - 1, spare, destination, source);
    }
}

void moveDisks(int disk, linkedStack<int> &source, linkedStack<int> &destination, linkedStack<int> &spare, char s, char d, char sp)
{
    if (disk == 0)
    {
        return;
    }
    moveDisks(disk - 1, source, spare, destination, s, sp, d);
    destination.push(source.pop());
    std::cout << "Move disk " << disk << " from " << s << " to " << d << std::endl;
    moveDisks(disk - 1, spare, destination, source, sp, d, s);
}
