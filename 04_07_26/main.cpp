#include <iostream>
#include <string>
#include <limits>

void resetStream();
int factorial(int n);

int inputInt(std::string prompt, std::string error, bool (*valid)(int, int, int), int lower = 0, int upper = 0);
bool intInRange(int n, int lower, int upper);
bool intGTX(int n, int x, int = 0);

int main()
{
    int n = inputInt("Enter a positive number: ", "That is not a positive number!", intGTX, -1);
    std::cout << factorial(n) << std::endl;

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