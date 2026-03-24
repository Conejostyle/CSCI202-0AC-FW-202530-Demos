#ifndef DONUT_H
#define DONUT_H
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <stdexcept>

enum icingType
{
    CHOCOLATEICING,
    CARAMELICING,
    MAPLE,
    VANILLA,
    GLAZE,
    SPECIALICE,
    NOICE
};

enum class drizzleType
{
    CARAMELDRIZZLE,
    CHOCOLATEDRIZZLE,
    PEANUTBUTTER,
    RASPBERRY,
    SPECIALDRIZZLE,
    NODRIZZLE
};

class donut
{
public:
    enum toppingType
    {
        RAINBOWSPR,
        CHOCOLATESPR,
        PEANUTS,
        COCONUT,
        OREO,
        BACON,
        GRAHAM,
        FRUITYPEBBLES,
        REESESPIECES,
        MMS,
        CANDYBAR,
        CHOCOLATECHIPS,
        SEASALT,
        CINSUGAR,
        POWDSUGAR,
        NOTOP
    };
    donut();
    donut(std::string icing, std::string topping, std::string drizzle);
    icingType getIcing() const;
    drizzleType getDrizzle() const;
    toppingType getTopping() const;
    void setIcing(std::string);
    void setTopping(std::string);
    void setDrizzle(std::string);
    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &, const donut &);
    const static std::map<icingType, std::string> iceToStr;
    const static std::map<std::string, icingType> strToIce;
    const static std::map<drizzleType, std::string> drizzleToStr;
    const static std::map<std::string, drizzleType> strToDrizzle;
    const static std::map<toppingType, std::string> topToStr;
    const static std::map<std::string, toppingType> strToTop;

private:
    icingType icing;
    toppingType topping;
    drizzleType drizzle;
};

#endif