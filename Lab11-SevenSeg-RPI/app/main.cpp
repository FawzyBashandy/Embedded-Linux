#include <IOStream.hpp>
#include <SevenSegment.hpp>

int main() {
    // --- Configure Seven Segment pins ---
    Sseg_Pins_t ssegPins = {
        {MCAL::GPIO::GPIO_PIN_4},  // a
        {MCAL::GPIO::GPIO_PIN_17}, // b
        {MCAL::GPIO::GPIO_PIN_27}, // c
        {MCAL::GPIO::GPIO_PIN_22}, // d
        {MCAL::GPIO::GPIO_PIN_5},  // e
        {MCAL::GPIO::GPIO_PIN_6},  // f
        {MCAL::GPIO::GPIO_PIN_13}, // g
        {MCAL::GPIO::GPIO_PIN_19}  // dot
    };

    Sseg_config_t ssegConfig = { ssegPins, DotEnable };

    // --- Create streams ---
    IStream* inputStream = new IOStream();
    OStream* terminalOutput = new IOStream();
    OStream* sevenSegOutput = new SevenSegment(ssegConfig);

    // --- Check Seven Segment initialization ---
    SevenSegment* sevenSegPtr = dynamic_cast<SevenSegment*>(sevenSegOutput);
    if (!sevenSegPtr || sevenSegPtr->getInitStatus() != SSEG_STATUS_OK) {
        std::cerr << "Seven Segment Initialization Failed!" << std::endl;
        delete inputStream;
        delete terminalOutput;
        delete sevenSegOutput;
        return -1;
    }

    // --- Main loop ---
    int digit = 0;
    while (true) {
        if (inputStream->readDigit(digit)) {
            terminalOutput->writeDigit(digit);   // write to terminal
            sevenSegOutput->writeDigit(digit);   // write to seven segment
        } else {
            std::cout << "Invalid input. Please enter a digit between 0 and 9." << std::endl;
        }
    }

    // --- Clean up (never reached in this loop, but good practice) ---
    delete inputStream;
    delete terminalOutput;
    delete sevenSegOutput;

    return 0;
}
