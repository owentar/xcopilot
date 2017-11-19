#ifndef X_COPILOT_UTILS_H
#define X_COPILOT_UTILS_H

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "boost/algorithm/string.hpp"
#include "boost/algorithm/string/split.hpp"

std::map<std::string, int> WORD_TO_NUMBER = {
        { "zero", 0 },
        { "one", 1 },
        { "two", 2 },
        { "three", 3 },
        { "four", 4 },
        { "five", 5 },
        { "six", 6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine", 9 }
};

std::vector<int> parseNumbers(const std::string& numbersAsWords)
{
    std::vector<std::string> numbers;
    boost::split(numbers, numbersAsWords, boost::is_any_of(" "));
    std::vector<int> result(numbers.size());
    std::transform(numbers.begin(), numbers.end(), result.begin(), [](const std::string& num) { return WORD_TO_NUMBER[num]; });
    return result;
}

double parseToNumber(const std::string& numbersAsWords, unsigned short decimals=0)
{
    std::vector<int> numbers = parseNumbers(numbersAsWords);
    double exp = numbers.size() - 1.0 - decimals;
    double scale = std::pow(10.0, exp);
    return std::accumulate(numbers.begin(), numbers.end(), 0.0, [&scale](double result, double number) {
        result += number * scale;
        scale /= 10;
        return result;
    });
}

int parseToInt(const std::string& numbersAsWords)
{
    return parseToNumber(numbersAsWords);
}

double parseToDecimal(const std::string& numbersAsWords, unsigned short decimals)
{
    return parseToNumber(numbersAsWords, decimals);
}

#endif //X_COPILOT_UTILS_H