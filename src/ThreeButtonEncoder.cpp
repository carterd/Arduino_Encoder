#include "ThreeButtonEncoder.h"

/**
 * @brief Construct a new Three Button Encoder:: Button Encoder object with the PINs of the three buttons
 * 
 * @param leftButtonPin Pin number of the left button
 * @param rightButtonPin Pin number of the right button
 * @param enterButtonPin Pin number of the enter button
 * @param pressedPinStatus Pin status indicating button is pressed
 * @param buttonPinMode Pin mode of the buttons either INPUT_PULLUP or INPUT_PULLDOWN
 */
ThreeButtonEncoder::ThreeButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode) 
    : ButtonEncoder(leftButtonPin, rightButtonPin, enterButtonPin, pressedPinStatus, buttonPinMode) {
}

/**
 * @brief 
 * 
 * @param leftButtonState This will be updated due to button input for left button
 * @param rightButtonState This will be updated due to button input for right button
 * @param enterButtonState This will be updated due to button input for enter button
 */
void ThreeButtonEncoder::readButtons() {
    this->mLeftButtonPressed = digitalRead(this->mLeftButtonPin) == this->mPressedPinStatus;
    this->mRightButtonPressed = digitalRead(this->mRightButtonPin) == this->mPressedPinStatus;
    this->mEnterButtonPressed = digitalRead(this->mEnterButtonPin) == this->mPressedPinStatus;
}
