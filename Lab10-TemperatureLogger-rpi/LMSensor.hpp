
#pragma once

#include "TemperatureData.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <memory>
class LM35Sensor
{
    private:
    int serialFile_ = -1;
    std::shared_ptr<TemperatureData> pT_ = std::make_shared<TemperatureData>(TemperatureData(0.0));
    public:
    LM35Sensor()=delete;
    LM35Sensor(const LM35Sensor&)=delete;
    LM35Sensor& operator= (const LM35Sensor&)=delete;
    LM35Sensor(std::string serialPath);
    void readTemperature();
    std::shared_ptr<TemperatureData> getTemperature()const;
};