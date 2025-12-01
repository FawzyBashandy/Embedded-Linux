#include <GPIO.hpp>
#include <iostream>
#include <stdint.h>
namespace MCAL {
namespace GPIO {
// Initialize GPIO STATIC MEMBERS
int GPIO::fdExport = -1;
int GPIO::fdUnExport = -1;
int GPIO::openedDirFds[28] = {
    0}; // cuz it's impossible to get a 0 fd especially in LINUX
int GPIO::openedValFds[28] = {0};
eGPIO_Status_t GPIO::enablePin(eGPIO_Pin_Number_t piN) {
  eGPIO_Status_t status;
  int temp = piN + 512;
  std::string pinStr = std::to_string(temp);
  if (fdExport == -1) {
    std::cout << "trying to open " << exportPath << "\n";
    fdExport = open(exportPath.c_str(), O_WRONLY, 0644);
  }
  if (write(fdExport, pinStr.c_str(), pinStr.size()) == -1) {
    status = GPIO_Status_FILE_ERROR;
    std::cout << "File not opened";
  } else {
    status = GPIO_Status_OK;
    std::cout << "export path opened";
  }
  return status;
}

eGPIO_Status_t GPIO::disablePin(eGPIO_Pin_Number_t piN) {
  eGPIO_Status_t status;
  int temp = piN + 512;
  std::string pinStr = std::to_string(temp);
  if (fdUnExport == -1) {
    fdUnExport = open(unexportPath.c_str(), O_WRONLY, 0644);
  }
  if (write(fdUnExport, pinStr.c_str(), pinStr.size()) == -1) {
    status = GPIO_Status_FILE_ERROR;
  } else {
    status = GPIO_Status_OK;
  }

  return status;
}
eGPIO_Status_t GPIO::setDirection(eGPIO_Pin_Number_t piN,
                                  ePin_Direction_t dir) {
  eGPIO_Status_t status;
  std::string dirPath = basePath + "gpio" + std::to_string(piN+512) + "/direction";
  std::string data;
  uint8_t temp = 0;
  if (openedDirFds[piN] == 0) {
    openedDirFds[piN] = open(dirPath.c_str(), O_WRONLY, 0644);
  }
  data = (dir == PIN_OUTPUT ? "out" : "in");
  lseek(openedDirFds[piN], 0, SEEK_SET);
  temp = write(openedDirFds[piN], data.c_str(), data.size());
  if (openedDirFds[piN] == -1 || temp == -1) {
    status = GPIO_Status_FILE_ERROR;
  } else {
    status = GPIO_Status_OK;
  }
  return status;
}
eGPIO_Status_t GPIO::writePin(eGPIO_Pin_Number_t piN, ePin_Logic_t logic) {
  eGPIO_Status_t status;
  std::string valPath = basePath + "gpio" + std::to_string(piN+512) + "/value";
  char value = (logic == PIN_HIGH ? '1' : '0');
  uint8_t temp = 0;

  if (openedValFds[piN] == 0) {
    openedValFds[piN] = open(valPath.c_str(), O_WRONLY, 0644);
  }
  lseek(openedValFds[piN], 0, SEEK_SET);
  temp = write(openedValFds[piN], &value, 1);

  if (openedValFds[piN] == -1 || temp == -1) {
    status = GPIO_Status_FILE_ERROR;
  } else {
    status = GPIO_Status_OK;
  }
  return status;
}
eGPIO_Status_t GPIO::readPin(eGPIO_Pin_Number_t piN, ePin_Logic_t &currLogic) {
  // TODO , check if it's output before read..
  eGPIO_Status_t status;
  std::string valPath = basePath + "gpio" + std::to_string(piN+512) + "/value";
  char value;
  uint8_t temp = 0;
  if (openedValFds[piN] == 0) {
    openedValFds[piN] = open(valPath.c_str(), O_RDWR, 0644);
  }
  lseek(openedValFds[piN], 0, SEEK_SET);
  temp = read(openedValFds[piN], &value, 1);
  if (temp == 1)
    currLogic = (value == '1') ? PIN_HIGH : PIN_LOW;

  if (openedValFds[piN] == -1 || temp == -1) {
    status = GPIO_Status_FILE_ERROR;
  } else {
    status = GPIO_Status_OK;
  }
  return status;
}

GPIOPin::GPIOPin(eGPIO_Pin_Number_t pin) {
  std::cout << "GPIOPin Constructor Called";
  this->pin = pin;
  GPIO::enablePin(pin);
}
eGPIO_Status_t GPIOPin::setDirection(ePin_Direction_t dir) {
  return GPIO::setDirection(pin, dir);
}
eGPIO_Status_t GPIOPin::writePin(ePin_Logic_t logic) {
  return GPIO::writePin(pin, logic);
}
eGPIO_Status_t GPIOPin::readPin(ePin_Logic_t &currLogic) {
  return GPIO::readPin(pin, currLogic);
}

GPIOPin::~GPIOPin() {
  close(GPIO::openedDirFds[pin]);
  close(GPIO::openedValFds[pin]);
  GPIO::disablePin(pin);
}
}; // namespace GPIO
}; // namespace MCAL