#pragma once

#include <iostream>
#include <memory>
#include "TemperatureData.hpp"
class Logger
{
    private:
    int logFile_;
    public:
    Logger()=delete;
    Logger(const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;

    Logger(std::string filePath);
    void logTemperature(std::shared_ptr<TemperatureData> data) const;
    void changeLogFile(std::string filePath);
    ~Logger();
};