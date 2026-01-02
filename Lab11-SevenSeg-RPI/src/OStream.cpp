#include "OStream.hpp"
#include <iostream>
OStream::OStream()
{
    std::cout << "OStream Constructor Called" << std::endl;
}
OStream::~OStream()
{
    std::cout << "OStream Destructor Called" << std::endl;
}