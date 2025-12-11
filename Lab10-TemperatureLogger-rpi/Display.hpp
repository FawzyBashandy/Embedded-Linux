#pragma once

#include <memory>
#include "TemperatureData.hpp"
class Display
{
    public:
    Display()=default;
    void displayTemperature(std::weak_ptr<TemperatureData> data);
};