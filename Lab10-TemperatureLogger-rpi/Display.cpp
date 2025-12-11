#include "Display.hpp"
#include "iostream"
void Display::displayTemperature(std::weak_ptr<TemperatureData> receivedTemp)
{
  std::shared_ptr<TemperatureData> data;
  if(!receivedTemp.expired())
  {
    data = receivedTemp.lock();
  }
  else
  {
    std::perror("No Temperature Received");
    return;
  }
  std::string temperatureString = std::to_string(data->getTimeStamp()) + " : " +
                                  std::to_string(data->getTemperature()) +
                                  " °C\n";
    std::cout << temperatureString;
}