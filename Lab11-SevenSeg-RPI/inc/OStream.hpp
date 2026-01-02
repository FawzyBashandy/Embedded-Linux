#pragma once

#include "Stream.hpp"
class OStream : virtual public Stream
{
    public:
    OStream();
    virtual void writeDigit(int d) = 0;

    virtual ~OStream() = 0; //To make class not instantiable.
};