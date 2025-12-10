
#pragma once

#include "TemperatureData.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
class LM35Sensor
{
    private:
    int serialFile_;
    public:
    LM35Sensor()=delete;
    LM35Sensor(const LM35Sensor&)=delete;
    LM35Sensor& operator= (const LM35Sensor&)=delete;
    LM35Sensor(std::string serialPath);
    TemperatureData readTemperature()const;
};