#include <iostream>
#include <string>
#include <limits>
#include "donut.h"
#include "order.h"

void referencePointers(donut *&, donut *);
void references(donut *&, donut &); // works the same as the one above
bool intInRange(int num, int low, int high);
int getInt(std::string prompt, std::string error, int low = 0, int high = 0, bool (*valid)(int, int, int) = intInRange);
bool gt0(int num, int low = 0, int high = 0);

void resetStream();

void codeGradeLoopFix(std::string errLocation);
std::string getIcing();
std::string getTopping(std::string);
std::string getDrizzle();
void icingPrompt();
void drizzlePrompt();
void toppingPrompt(std::string);

int main()
{
    donut *pointer1;
    donut myDonut;
    pointer1 = new donut("caramel", "Bacon", "Raspberry");
    referencePointers(pointer1, &myDonut);
    int numDonuts = getInt("How many donuts would you like? ", "That is not a valid number of donuts! Please enter a number between 1 and 12", 1, 12);

    Order donutOrder;
    for (int i = 0; i < numDonuts; i++)
    {
        std::string icing = getIcing();
        std::string topping = getTopping(icing);
        std::string drizzle = getDrizzle();
        donut d(icing, topping, drizzle);
        donutOrder + d;
    }
    std::cout << donutOrder << std::endl;

    return 0;
};

void referencePointers(donut *&p, donut *d)
{
    d->setDrizzle("Peanut butter");
    donut *temp = p;
    p = d;
    d = temp;
    delete temp;
}
void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

bool intInRange(int num, int low, int high)
{

    return num >= low && num <= high;
}

int getInt(std::string prompt, std::string error, int low, int high, bool (*valid)(int, int, int))
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    while (!std::cin || !valid(num, low, high))
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << error << std::endl;
        std::cout << prompt;
        std::cin >> num;
    }

    return num;
}

bool gt0(int num, int low, int high)
{
    return num > 0;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation);
    }
}

std::string getIcing()
{
    std::string ice;
    icingPrompt();
    std::cin >> std::ws;
    std::getline(std::cin, ice);
    std::string icingLower = ice;
    std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    while (!donut::strToIce.count(icingLower))
    {
        codeGradeLoopFix("main.cpp::getIcing()");
        // resetStream();
        std::cout << ice << " is not a valid choice. " << std::endl;
        icingPrompt();
        std::cin >> std::ws;
        std::getline(std::cin, ice);
        icingLower = ice;
        std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    }
    return ice;
}

std::string getTopping(std::string icing)
{
    std::string top;
    std::transform(icing.begin(), icing.end(), icing.begin(), ::tolower);
    toppingPrompt(icing);
    std::cin >> std::ws;
    std::getline(std::cin, top);
    std::string topCopy = top;
    std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
    if (icing == "none")
    {
        while (topCopy != "cinnamon sugar" && topCopy != "powdered sugar" && topCopy != "none")
        {
            codeGradeLoopFix("main.cpp::getTopping(\"none\")");
            std::cout << top << "is not valid for icing " << icing << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    else
    {
        while (!donut::strToTop.count(topCopy))
        {
            codeGradeLoopFix("main.cpp::getTopping()");
            std::cout << top << " is not a valid topping." << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    return top;
}

void icingPrompt()
{
    std::cout << "Choose your icing from the choices below: " << std::endl;
    for (std::map<icingType, std::string>::const_iterator it = donut::iceToStr.begin(); it != donut::iceToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

std::string getDrizzle()
{
    std::string drizzle;
    drizzlePrompt();
    std::cin >> std::ws;
    std::getline(std::cin, drizzle);
    std::string drizzleLower = drizzle;
    std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    while (!donut::strToDrizzle.count(drizzleLower))
    {
        codeGradeLoopFix("main.cpp::getDrizzle()");
        std::cout << drizzle << " is not a valid drizzle choice." << std::endl;
        drizzlePrompt();
        std::cin >> std::ws;
        std::getline(std::cin, drizzle);
        drizzleLower = drizzle;
        std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    }
    return drizzle;
}

void drizzlePrompt()
{
    std::cout << "Choose your drizzle from the choices below:" << std::endl;
    for (std::map<drizzleType, std::string>::const_iterator it = donut::drizzleToStr.begin(); it != donut::drizzleToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

void toppingPrompt(std::string icing)
{
    std::cout << "Choose your topping from the choices below:" << std::endl;
    if (icing == "none")
    {
        std::cout << "Cinnamon Sugar" << std::endl;
        std::cout << "Powdered Sugar" << std::endl;
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto it = donut::topToStr.begin(); it != donut::topToStr.end(); ++it)
        {
            std::cout << it->second << std::endl;
        }
    }
}
