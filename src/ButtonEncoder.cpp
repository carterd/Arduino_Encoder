#include "ButtonEncoder.h"
#include <lvgl.h>

/**
 * @brief Construct a new Button Encoder:: Button Encoder object with the PINs of the three buttons
 * 
 * @param leftButtonPin Pin number of the left button
 * @param rightButtonPin Pin number of the right button
 * @param enterButtonPin Pin number of the enter button
 * @param pressedPinStatus Pin status indicating button is pressed
 * @param buttonPinMode Pin mode of the buttons either INPUT_PULLUP or INPUT_PULLDOWN
 */
ButtonEncoder::ButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, pin_size_t enterButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode) {
    this->mLeftButtonPin = leftButtonPin;
    this->mRightButtonPin = rightButtonPin;
    this->mEnterButtonPin = enterButtonPin;
    this->mPressedPinStatus = pressedPinStatus;
    // Set the pins to read
    pinMode(this->mLeftButtonPin, buttonPinMode);
    pinMode(this->mRightButtonPin, buttonPinMode);
    pinMode(this->mEnterButtonPin, buttonPinMode);
}

/**
 * @brief Read the current state of the encoder, i.e. what buttons are pressed
 * 
 */
void ButtonEncoder::update() {
    // Read the buttons
    this->readButtons();
    // Set the keypressed and last-keypressed to expose
    bool keyPressed = true;
    if (this->mLeftButtonPressed && !this->mRightButtonPressed && !this->mEnterButtonPressed) {
        this->mLastKeyPressed = EncoderKey::ENCODER_LEFT;
    } else if (this->mRightButtonPressed && !this->mLeftButtonPressed && !this->mEnterButtonPressed) {
        this->mLastKeyPressed = EncoderKey::ENCODER_RIGHT;
    } else if (this->mEnterButtonPressed && !this->mLeftButtonPressed && !this->mRightButtonPressed) {
        this->mLastKeyPressed = EncoderKey::ENCODER_ENTER;
    }
    else {
        keyPressed = false;
    }
    this->mKeyPressed = keyPressed;
}