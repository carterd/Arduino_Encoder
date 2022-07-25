#include "ButtonEncoder.h"

/**
 * @brief Construct a new Button Encoder:: Button Encoder object with the PINs of the three buttons
 * 
 * @param leftButtonPin Pin number of the left button
 * @param rightButtonPin Pin number of the right button
 * @param enterButtonPin Pin number of the enter button
 * @param pressedPinStatus Pin status indicating button is pressed
 * @param buttonPinMode Pin mode of the buttons either INPUT_PULLUP or INPUT_PULLDOWN
 */
ButtonEncoder::ButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus, int buttonPinMode) {
    mLeftButtonPin = leftButtonPin;
    mRightButtonPin = rightButtonPin;
    mEnterButtonPin = enterButtonPin;
    mPressedPinStatus = pressedPinStatus;

    pinMode(mLeftButtonPin, buttonPinMode);
    pinMode(mRightButtonPin, buttonPinMode);
    pinMode(mEnterButtonPin, buttonPinMode);
}
/**
 * @brief Read the current state of the encoder, i.e. what buttons are pressed
 * 
 */
void ButtonEncoder::readEncoder() {
    bool leftButtonPressed = digitalRead(mLeftButtonPin) == mPressedPinStatus;
    bool rightButtonPressed = digitalRead(mRightButtonPin) == mPressedPinStatus;
    bool enterButtonPressed = digitalRead(mEnterButtonPin) == mPressedPinStatus;

    bool keyPressed = true;
    if (leftButtonPressed && !rightButtonPressed && !enterButtonPressed) {
        mLastKeyPressed = EncoderKey::ENCODER_LEFT;
    } else if (rightButtonPressed && !leftButtonPressed && !enterButtonPressed) {
        mLastKeyPressed = EncoderKey::ENCODER_RIGHT;
    } else if (enterButtonPressed && !leftButtonPressed && !rightButtonPressed) {
        mLastKeyPressed = EncoderKey::ENCODER_ENTER;
    } else {
        keyPressed = false;
    }
    mKeyPressed = keyPressed;
}