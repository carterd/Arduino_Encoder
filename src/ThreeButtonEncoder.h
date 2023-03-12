#ifndef _THREE_BUTTON_ENCODER_H_
#define _THREE_BUTTON_ENCODER_H_

#include "ButtonEncoder.h"

class ThreeButtonEncoder : public ButtonEncoder {
public:
    ThreeButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode);
    virtual ~ThreeButtonEncoder() {}
protected:
    virtual void readButtons();
};

#endif