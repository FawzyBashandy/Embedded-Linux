#pragma once

#include "Stream.hpp"

class IStream : virtual public Stream
{
    private:
    bool isValidDigit(int &digit) const;
    
    public:
    IStream();
    virtual ~IStream() = 0; //To make class not instantiable.
    bool readDigit(int& digit);

};