#include "donut.h"

donut::donut()
{
    topping = NOTOP;
    icing = NOICE;
    drizzle = drizzleType::NODRIZZLE;
}

donut::donut(std::string icing, std::string topping, std::string drizzle)
{
    setIcing(icing);
    setDrizzle(drizzle);
    setTopping(topping);
}

icingType donut::getIcing() const
{
    return icing;
}

drizzleType donut::getDrizzle() const
{
    return drizzle;
}

donut::toppingType donut::getTopping() const
{
    return topping;
}

void donut::setIcing(std::string ice)
{
    std::transform(ice.begin(), ice.end(), ice.begin(), ::tolower);
    if (!strToIce.count(ice))
    {
        throw std::invalid_argument(ice + " is not a valid icing!");
    }
    icing = strToIce.at(ice);
}

void donut::setTopping(std::string top)
{
    std::transform(top.begin(), top.end(), top.begin(), ::tolower);
    if (!strToTop.count(top))
    {
        throw std::invalid_argument(top + " is not a valid icing!");
    }
    topping = strToTop.at(top);
}

void donut::setDrizzle(std::string driz)
{
    std::transform(driz.begin(), driz.end(), driz.begin(), ::tolower);
    if (!strToDrizzle.count(driz))
    {
        throw std::invalid_argument(driz + " is not a valid icing!");
    }
    this->drizzle = strToDrizzle.at(driz);
}

std::string donut::toString() const
{
    std::string out;
    out = "Icing: " + iceToStr.at(icing) + " Topping: " + topToStr.at(topping) + " Drizzle: " + drizzleToStr.at(drizzle);
    return out;
}

std::ostream &operator<<(std::ostream &out, const donut &d)
{
    out << d.toString();
    return out;
}

const std::map<icingType, std::string> donut::iceToStr = {{CHOCOLATEICING, "Chocolate"},
                                                          {CARAMELICING, "Caramel"},
                                                          {MAPLE, "Maple"},
                                                          {VANILLA, "Vanilla"},
                                                          {GLAZE, "Glaze"},
                                                          {SPECIALICE, "Special"},
                                                          {NOICE, "None"}};
const std::map<std::string, icingType> donut::strToIce = {{"chocolate", CHOCOLATEICING},
                                                          {"caramel", CARAMELICING},
                                                          {"maple", MAPLE},
                                                          {"vanilla", VANILLA},
                                                          {"glaze", GLAZE},
                                                          {"special", SPECIALICE},
                                                          {"none", NOICE}};
const std::map<donut::toppingType, std::string> donut::topToStr =
    {{RAINBOWSPR, "Rainbow Sprinkles"},
     {CHOCOLATESPR, "Chocolate Sprinkles"},
     {PEANUTS, "Peanuts"},
     {COCONUT, "Coconut"},
     {OREO, "Oreo"},
     {BACON, "Bacon"},
     {GRAHAM, "Graham"},
     {FRUITYPEBBLES, "Fruity Pebbles"},
     {REESESPIECES, "Reeses Pieces"},
     {MMS, "M&Ms"},
     {CANDYBAR, "Candy Bar"},
     {CHOCOLATECHIPS, "Chocolate Chips"},
     {SEASALT, "Sea Salt"},
     {CINSUGAR, "Cinnamon Sugar"},
     {POWDSUGAR, "Powdered Sugar"},
     {NOTOP, "None"}};

const std::map<std::string, donut::toppingType> donut::strToTop =
    {
        {"rainbow sprinkles", RAINBOWSPR},
        {"chocolate sprinkles", CHOCOLATESPR},
        {"peanuts", PEANUTS},
        {"coconut", COCONUT},
        {"oreo", OREO},
        {"bacon", BACON},
        {"graham", GRAHAM},
        {"fruity pebbles", FRUITYPEBBLES},
        {"reeses pieces", REESESPIECES},
        {"m&ms", MMS},
        {"candy bar", CANDYBAR},
        {"chocolate chips", CHOCOLATECHIPS},
        {"sea salt", SEASALT},
        {"cinnamon sugar", CINSUGAR},
        {"powdered sugar", POWDSUGAR},
        {"none", NOTOP}};
const std::map<drizzleType, std::string> donut::drizzleToStr =
    {{drizzleType::CARAMELDRIZZLE, "Caramel"},
     {drizzleType::CHOCOLATEDRIZZLE, "Chocolate"},
     {drizzleType::PEANUTBUTTER, "Peanut Butter"},
     {drizzleType::RASPBERRY, "Raspberry"},
     {drizzleType::SPECIALDRIZZLE, "Special"},
     {drizzleType::NODRIZZLE, "None"}};

const std::map<std::string, drizzleType> donut::strToDrizzle =
    {{"caramel", drizzleType::CARAMELDRIZZLE},
     {"chocolate", drizzleType::CHOCOLATEDRIZZLE},
     {"peanut butter", drizzleType::PEANUTBUTTER},
     {"raspberry", drizzleType::RASPBERRY},
     {"special", drizzleType::SPECIALDRIZZLE},
     {"none", drizzleType::NODRIZZLE}};
