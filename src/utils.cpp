#include "utils.hpp"

std::string padString(const std::string &str, const size_t &amount, const char &padChar)
{
    std::string pad;
    for (size_t i = 0; i < amount; i++)
    {
        pad += padChar;
    }
    return pad + str + pad;
}

std::string formatNumber(const double number)
{
    // Insert commas every 3 digits before the decimal point
    std::string numStr = std::to_string(number);
    int decimalPos = numStr.find(".");
    std::string decimal = numStr.substr(decimalPos);
    int commaPos = decimalPos - 3;
    if (std::stod(decimal) == 0.0)
    {
        numStr = numStr.substr(0, decimalPos);
        commaPos = numStr.size() - 3;
    }
    while (commaPos > 0)
    {
        numStr.insert(commaPos, ",");
        commaPos -= 3;
    }
    return numStr;
}

std::string formatNumber(const std::string &number)
{
    std::string numStr = number;
    int decimalPos = numStr.find(".");
    int commaPos;

    if (decimalPos != std::string::npos)
    {
       commaPos = decimalPos - 3; 
    }else{
        commaPos = numStr.size() - 3;
    }

    while (commaPos > 0)
    {
        numStr.insert(commaPos, ",");
        commaPos -= 3;
    }
    return numStr;
}
