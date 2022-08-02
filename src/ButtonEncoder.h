#ifndef _BUTTON_ENCODER_H_
#define _BUTTON_ENCODER_H_

#include "Encoder.h"
#include <Arduino.h>

class ButtonEncoder : public Encoder {
public:
    
    ButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus = LOW, int buttonPinMode = INPUT_PULLUP);

    virtual void update();
protected:
    pin_size_t mLeftButtonPin;
    pin_size_t mRightButtonPin;
    pin_size_t mEnterButtonPin;
    PinStatus mPressedPinStatus;
private:
};

#endif