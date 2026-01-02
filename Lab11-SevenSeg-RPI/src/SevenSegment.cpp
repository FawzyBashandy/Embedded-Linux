#include "SevenSegment.hpp"
#include "GPIO.hpp"
#include <iostream>
eSseg_Number_t SevenSegment::lookupTable[10] = {
    NUMBER_0, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4,
    NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9};

SevenSegment::SevenSegment(Sseg_config_t &config)
    : a((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.a.pinNumber), b((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.b.pinNumber),
      c((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.c.pinNumber), d((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.d.pinNumber),
      e((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.e.pinNumber), f((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.f.pinNumber),
      g((MCAL::GPIO::eGPIO_Pin_Number_t)config.pins.g.pinNumber) 
{

  std::cout << "SevenSegment Constructor Called" << std::endl;
  a.setDirection(MCAL::GPIO::PIN_OUTPUT);
  b.setDirection(MCAL::GPIO::PIN_OUTPUT);
  c.setDirection(MCAL::GPIO::PIN_OUTPUT);
  d.setDirection(MCAL::GPIO::PIN_OUTPUT);
  e.setDirection(MCAL::GPIO::PIN_OUTPUT);
  f.setDirection(MCAL::GPIO::PIN_OUTPUT);
  g.setDirection(MCAL::GPIO::PIN_OUTPUT);

  if (config.isDotEnabled == DotEnable) {
    dot = std::make_unique<MCAL::GPIO::GPIOPin>(config.pins.dot.pinNumber);
    dot->setDirection(MCAL::GPIO::PIN_OUTPUT);
  }

  InitStatus = SSEG_STATUS_OK;
}
SevenSegment::~SevenSegment() {
  std::cout << "SevenSegment Destructor Called" << std::endl;
}

eSseg_Status_t SevenSegment::getInitStatus() const { return InitStatus; }

eSseg_Status_t SevenSegment::Sseg_writeNumber(eSseg_Number_t num) {
  eSseg_Status_t status;
  switch (num) {
  case NUMBER_NONE:
  case NUMBER_0:
  case NUMBER_1:
  case NUMBER_2:
  case NUMBER_3:
  case NUMBER_4:
  case NUMBER_5:
  case NUMBER_6:
  case NUMBER_7:
  case NUMBER_8:
  case NUMBER_9:
    break; // valid
  default:
    return SSEG_STATUS_INVALIDNUMBER; // invalid
  }

  status = SSEG_STATUS_OK;
  a.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 0) & 0x01))); // a
  b.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 1) & 0x01))); // b
  c.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 2) & 0x01))); // c
  d.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 3) & 0x01))); // d
  e.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 4) & 0x01))); // e
  f.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 5) & 0x01))); // f
  g.writePin(MCAL::GPIO::ePin_Logic_t(!((num >> 6) & 0x01))); // g

  if (dot != nullptr) {
    if (num != NUMBER_NONE)
      dot->writePin(MCAL::GPIO::ePin_Logic_t(MCAL::GPIO::PIN_LOW));
    else {
      dot->writePin(MCAL::GPIO::ePin_Logic_t(MCAL::GPIO::PIN_HIGH));
    }
  }

  return status;
}
void SevenSegment::writeDigit(int d) {
  if (d < 0 || d > 9) {
    std::cerr << "Invalid digit: " << d << std::endl;
    return;
  }
  eSseg_Status_t status = Sseg_writeNumber(lookupTable[d]);
  if (status != SSEG_STATUS_OK) {
    std::cerr << "Error writing number to Seven Segment Display" << std::endl;
  }
}