#include "LMSensor.hpp"
#include "../Lab9-GPIO-rpi/GPIO.hpp"
#include "TemperatureData.hpp"


LM35Sensor::LM35Sensor(std::string serialPath) : serialFile_{open(serialPath.c_str(),O_RDONLY)}
{
    if(serialFile_ == -1)
    {
        std::perror("File Couldn't be opened");
    }
}
TemperatureData LM35Sensor::readTemperature()const
{
    char Buffer[30];
    int nB = read(serialFile_,Buffer,sizeof(Buffer));
    if(nB == -1)
    {
        std::perror("File Read Error");
    }
    else if(nB==0)
    {
        std::cout<<"End of File reached!";
    }
    else
    {
        std::string temp(Buffer,nB);
        TemperatureData temperature{std::stof(temp)};
        return temperature;
    }
    return TemperatureData{0};
}