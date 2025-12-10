#include "GPIO.hpp"
#include <iostream>

int main(void) {
  std::cout << "Trial";
  MCAL::GPIO::GPIOPin pin17 = MCAL::GPIO::GPIOPin(MCAL::GPIO::GPIO_PIN_17);
    for (volatile int i = 0; i < 99999999; i++);
  auto pin27 = pin17[27];
    for (volatile int i = 0; i < 99999999; i++);
  pin17.setDirection(MCAL::GPIO::PIN_OUTPUT);

  pin27.setDirection(MCAL::GPIO::PIN_INPUT);

  MCAL::GPIO::ePin_Logic_t logic=MCAL::GPIO::PIN_HIGH;

  for (volatile int i = 0; i < 999999; i++) {
      pin27.readPin(logic);
      if (logic == MCAL::GPIO::PIN_LOW) {
        pin17.writePin(MCAL::GPIO::PIN_LOW);
      } else {
        pin17.writePin(MCAL::GPIO::PIN_HIGH);
      }
    
  }
}