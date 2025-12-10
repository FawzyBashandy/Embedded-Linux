#include "Display.hpp"
#include "Logger.hpp"
#include "TemperatureData.hpp"
#include "LMSensor.hpp"

int main(void)
{
    LM35Sensor sensor{"/dev/serial0"};
    Logger Logfile{"/home/pi/fooz.txt"};
    Display display;
    while(1){
    std::shared_ptr<TemperatureData> pT=std::make_shared<TemperatureData>(sensor.readTemperature());
    Logfile.logTemperature(pT);
    display.displayTemperature(pT);
    sleep(2);
    }


}