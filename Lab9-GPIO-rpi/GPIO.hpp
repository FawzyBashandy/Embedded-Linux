#include <iostream>
namespace MCAL {
namespace GPIO {
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
typedef enum { GPIO_Status_OK, GPIO_Status_InvalidPinNumber , GPIO_Status_FILE_ERROR } eGPIO_Status_t;
typedef enum { PIN_OUTPUT, PIN_INPUT } ePin_Direction_t;
typedef enum {
  GPIO_PIN_0 = 0,   // Physical pin 27, I2C ID_SD
  GPIO_PIN_1 = 1,   // Physical pin 28, I2C ID_SC
  GPIO_PIN_2 = 2,   // Physical pin 3, SDA1
  GPIO_PIN_3 = 3,   // Physical pin 5, SCL1
  GPIO_PIN_4 = 4,   // Physical pin 7, GPCLK0
  GPIO_PIN_5 = 5,   // Physical pin 29, GPCLK1
  GPIO_PIN_6 = 6,   // Physical pin 31, GPCLK2
  GPIO_PIN_7 = 7,   // Physical pin 26
  GPIO_PIN_8 = 8,   // Physical pin 24
  GPIO_PIN_9 = 9,   // Physical pin 21, SPI0 MISO
  GPIO_PIN_10 = 10, // Physical pin 19, SPI0 MOSI
  GPIO_PIN_11 = 11, // Physical pin 23, SPI0 SCLK
  GPIO_PIN_12 = 12, // Physical pin 32, PWM0
  GPIO_PIN_13 = 13, // Physical pin 33, PWM1
  GPIO_PIN_14 = 14, // Physical pin 8, UART TXD
  GPIO_PIN_15 = 15, // Physical pin 10, UART RXD
  GPIO_PIN_16 = 16, // Physical pin 36
  GPIO_PIN_17 = 17, // Physical pin 11
  GPIO_PIN_18 = 18, // Physical pin 12, PWM0
  GPIO_PIN_19 = 19, // Physical pin 35, SPI1 MISO
  GPIO_PIN_20 = 20, // Physical pin 38, SPI1 MOSI
  GPIO_PIN_21 = 21, // Physical pin 40, SPI1 SCLK
  GPIO_PIN_22 = 22, // Physical pin 15
  GPIO_PIN_23 = 23, // Physical pin 16
  GPIO_PIN_24 = 24, // Physical pin 18
  GPIO_PIN_25 = 25, // Physical pin 22
  GPIO_PIN_26 = 26, // Physical pin 37
  GPIO_PIN_27 = 27  // Physical pin 13
} eGPIO_Pin_Number_t;
typedef enum { PIN_LOW = 0, PIN_HIGH } ePin_Logic_t;

class GPIO {
private:
  GPIO();
  static int fdExport;
  static int fdUnExport;
  static inline const std::string basePath = "/sys/class/gpio/";
  static inline const std::string exportPath = "/sys/class/gpio/export";
  static inline const std::string unexportPath = "/sys/class/gpio/unexport";
public:
  static int  openedDirFds[28];
  static int  openedValFds[28];
  static eGPIO_Status_t enablePin(eGPIO_Pin_Number_t piN);
  static eGPIO_Status_t disablePin(eGPIO_Pin_Number_t piN);
  static eGPIO_Status_t setDirection(eGPIO_Pin_Number_t piN,
                                     ePin_Direction_t dir);
  static eGPIO_Status_t writePin(eGPIO_Pin_Number_t piN, ePin_Logic_t logic);
  static eGPIO_Status_t readPin(eGPIO_Pin_Number_t piN,
                                ePin_Logic_t &currLogic);
};
class GPIOPin {
private:
  eGPIO_Pin_Number_t pin;

public:
  GPIOPin(eGPIO_Pin_Number_t pin);
  eGPIO_Status_t setDirection(ePin_Direction_t dir);
  eGPIO_Status_t writePin(ePin_Logic_t logic);
  eGPIO_Status_t readPin(ePin_Logic_t &currLogic);

  ~GPIOPin();
};
}; // namespace GPIO

}; // namespace MCAL