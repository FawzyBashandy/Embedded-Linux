#include "Display.hpp"
#include "iostream"
void Display::displayTemperature(std::shared_ptr<TemperatureData> data)
{
  std::string temperatureString = std::to_string(data->getTimeStamp()) + " : " +
                                  std::to_string(data->getTemperature()) +
                                  " °C\n";
    std::cout << temperatureString;
}