#ifndef _TWO_BUTTON_ENCODER_H_
#define _TWO_BUTTON_ENCODER_H_

#include "ButtonEncoder.h"

class TwoButtonEncoder : public ButtonEncoder {
public:
    TwoButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode);

    virtual void update();
protected:
    virtual void readButtons();
    virtual ~TwoButtonEncoder() {}
private:
    enum class DebounceState { NO_BUTTON_PRESSED, NO_TO_LEFT_BUTTON, NO_TO_RIGHT_BUTTON, ENTER_BUTTON, ENTER_TO_LEFT_BUTTON, ENTER_TO_RIGHT_BUTTON };
    DebounceState mDebounceState = DebounceState::NO_BUTTON_PRESSED;
    int mDebounceCount = 4;
    int mCurrentDebouceCount;
};

#endif