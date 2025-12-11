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
    sensor.readTemperature();
    Logfile.logTemperature(sensor.getTemperature());
    display.displayTemperature(sensor.getTemperature());
    sleep(2);
    }


}