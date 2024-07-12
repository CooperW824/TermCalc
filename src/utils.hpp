#ifndef UTILS_HPP
#define UTILS_HPP


#include <string>

std::string padString(const std::string& str, const size_t& amount, const char& padChar = ' ');
std::string formatNumber(const double number);
std::string formatNumber(const std::string &number);

#endif // UTILS_HPP