#pragma once

#include "OStream.hpp"
#include "IStream.hpp"
class IOStream : public IStream , public OStream
{
    private:
    public:
    IOStream();
    ~IOStream();
    void writeDigit(int d)override;

};