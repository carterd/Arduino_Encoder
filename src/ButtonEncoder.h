#ifndef _BUTTON_ENCODER_H_
#define _BUTTON_ENCODER_H_

#include "Encoder.h"
#include <Arduino.h>

#ifdef ESP32    
    typedef uint8_t pin_size_t;
    typedef int PinStatus;
    typedef int PinMode; 
#endif

class ButtonEncoder : public Encoder {
public:
    ButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode);

    virtual void update();
    virtual ~ButtonEncoder() {}

protected:
    virtual void readButtons() = 0;
    bool mLeftButtonPressed;
    bool mRightButtonPressed;
    bool mEnterButtonPressed;
    pin_size_t mLeftButtonPin;
    pin_size_t mRightButtonPin;
    pin_size_t mEnterButtonPin;
    PinStatus mPressedPinStatus;
};

#endif