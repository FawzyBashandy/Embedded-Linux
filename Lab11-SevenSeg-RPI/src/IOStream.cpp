#include "IOStream.hpp"
#include <iostream>

IOStream::IOStream()
{
    std::cout << "IOStream Constructor Called" << std::endl;
}
IOStream::~IOStream()
{
    std::cout << "IOStream Destructor Called" << std::endl;
}
void IOStream::writeDigit(int d)
{
    std::cout << "Writing digit: " << d << std::endl;
}