#pragma once

#include <memory>
#include "TemperatureData.hpp"
class Display
{
    public:
    Display()=default;
    void displayTemperature(std::shared_ptr<TemperatureData> data);
};