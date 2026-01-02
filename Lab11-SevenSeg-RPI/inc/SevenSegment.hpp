#pragma once

#include "IStream.hpp"
#include "OStream.hpp"
#include "GPIO.hpp"
#include <memory>
typedef enum {
  SSEG_STATUS_OK,
  SSEG_STATUS_WRONGCONFIG,
  SSEG_STATUS_INVALIDNUMBER
} eSseg_Status_t;
typedef enum {
  NUMBER_0 = 0b0111111, // a b c d e f
  NUMBER_1 = 0b0000110, // b c
  NUMBER_2 = 0b1011011, // a b d e g
  NUMBER_3 = 0b1001111, // a b c d g
  NUMBER_4 = 0b1100110, // b c f g
  NUMBER_5 = 0b1101101, // a c d f g
  NUMBER_6 = 0b1111101, // a c d e f g
  NUMBER_7 = 0b0000111, // a b c
  NUMBER_8 = 0b1111111, // a b c d e f g
  NUMBER_9 = 0b1101111,  // a b c d f g
  NUMBER_NONE = 0b0000000
} eSseg_Number_t;


typedef struct {
  MCAL::GPIO::eGPIO_Pin_Number_t pinNumber;
} Sseg_Pin_t;

typedef struct {
  Sseg_Pin_t a;
  Sseg_Pin_t b;
  Sseg_Pin_t c;
  Sseg_Pin_t d;
  Sseg_Pin_t e;
  Sseg_Pin_t f;
  Sseg_Pin_t g;
  Sseg_Pin_t dot;
} Sseg_Pins_t;

typedef enum { DotDisable, DotEnable } eSSeg_DotState_t;

typedef struct {
  Sseg_Pins_t pins;
  eSSeg_DotState_t isDotEnabled;
} Sseg_config_t;

class SevenSegment : public IStream , public OStream
{
    private:
    eSseg_Status_t InitStatus;

    MCAL::GPIO::GPIOPin a;
    MCAL::GPIO::GPIOPin b;
    MCAL::GPIO::GPIOPin c;
    MCAL::GPIO::GPIOPin d;
    MCAL::GPIO::GPIOPin e;
    MCAL::GPIO::GPIOPin f;
    MCAL::GPIO::GPIOPin g;
    std::unique_ptr<MCAL::GPIO::GPIOPin> dot;

    static eSseg_Number_t lookupTable[10];

    eSseg_Status_t Sseg_writeNumber(eSseg_Number_t num);
    public:
    SevenSegment(Sseg_config_t &config);
    ~SevenSegment();
    eSseg_Status_t getInitStatus() const;
    void writeDigit(int d) override;
};