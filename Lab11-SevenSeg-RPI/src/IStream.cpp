#include "IStream.hpp"
#include <iostream>

bool IStream::isValidDigit(int &digit) const
{
    return (digit >= 0 && digit <= 9);
}

bool IStream::readDigit(int &digit)
{
    std::cout << "Enter a digit (0-9): ";

    if (!(std::cin >> digit))   // stream failure check
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return false;
    }

    return isValidDigit(digit);
}

IStream::IStream()
{
    std::cout << "IStream Constructor Called" << std::endl;
}
IStream::~IStream()
{
    std::cout << "IStream Destructor Called" << std::endl;
}