#include "TemperatureData.hpp"
#include <ctime>

TemperatureData::TemperatureData(float temperature):temperature_{temperature} , timestamp_{std::time(nullptr)}
{

}

void TemperatureData::ChangeTemperature(float temperature)
{
    temperature_ = temperature;
    timestamp_ = std::time(nullptr);
}
float TemperatureData::getTemperature() const
{
    return temperature_;
}
std::time_t TemperatureData::getTimeStamp() const
{
    return timestamp_;
}