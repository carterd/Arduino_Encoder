#include "TwoButtonEncoder.h"

/**
 * @brief Construct a new Button Encoder:: Button Encoder object with the only two buttons
 * 
 * @param leftButtonPin Pin number of the left button
 * @param rightButtonPin Pin number of the right button
 * @param pressedPinStatus Pin status indicating button is pressed
 * @param buttonPinMode Pin mode of the buttons either INPUT_PULLUP or INPUT_PULLDOWN
 */
TwoButtonEncoder::TwoButtonEncoder(pin_size_t leftButtonPin, pin_size_t rightButtonPin, PinStatus pressedPinStatus, PinMode buttonPinMode) :
    ButtonEncoder(leftButtonPin, rightButtonPin, 0, pressedPinStatus, buttonPinMode) {
}

/**
 * @brief This will read the state of the buttons
 * 
 * @param leftButtonState This will be updated due to button input for left button
 * @param rightButtonState This will be updated due to button input for right button
 * @param enterButtonState This will be updated due to button input for enter button
 */
void TwoButtonEncoder::readButtons() {
    this->mLeftButtonPressed = digitalRead(this->mLeftButtonPin) == this->mPressedPinStatus;
    this->mRightButtonPressed = digitalRead(this->mRightButtonPin) == this->mPressedPinStatus;

    // Enter has been pressed
    this->mEnterButtonPressed = false;
    if (this->mLeftButtonPressed && this->mRightButtonPressed)
    {
        this->mDebounceState = DebounceState::ENTER_BUTTON;
        this->mLeftButtonPressed = false;
        this->mRightButtonPressed = false;
        this->mEnterButtonPressed = true;
    }
    // Button state is fully released
    else if (!this->mLeftButtonPressed && !this->mRightButtonPressed)
    {
        switch (this->mDebounceState) {
            case DebounceState::NO_TO_LEFT_BUTTON:
                this->mLeftButtonPressed = true;
                break;
            case DebounceState::NO_TO_RIGHT_BUTTON:
                this->mRightButtonPressed = true;
                break;
        }
        this->mDebounceState = DebounceState::NO_BUTTON_PRESSED;
    }
    // Button state is left
    else if (this->mLeftButtonPressed && !this->mRightButtonPressed) 
    {
        switch (this->mDebounceState) {
            case DebounceState::NO_BUTTON_PRESSED:
                this->mDebounceState = DebounceState::NO_TO_LEFT_BUTTON;
                // Delay left button pressed for debounce count
                this->mCurrentDebouceCount = this->mDebounceCount;
                this->mLeftButtonPressed = false;
                break;
            case DebounceState::NO_TO_LEFT_BUTTON:
                // Delay left button pressed for debounce count
                if (this->mCurrentDebouceCount) { this->mCurrentDebouceCount--; }
                if (this->mCurrentDebouceCount) { this->mLeftButtonPressed = false; }
                break;
            case DebounceState::NO_TO_RIGHT_BUTTON:
                this->mDebounceState = DebounceState::NO_TO_LEFT_BUTTON;
                // Send right button pressed then start debounce count for left
                this->mCurrentDebouceCount = this->mDebounceCount;
                this->mLeftButtonPressed = false;
                this->mRightButtonPressed = true;
                break;
            case DebounceState::ENTER_BUTTON:
                this->mDebounceState = DebounceState::ENTER_TO_LEFT_BUTTON;
                // Hide the left button after hitting enter state
                this->mLeftButtonPressed = false;
                break;
            case DebounceState::ENTER_TO_LEFT_BUTTON:
                // Hide the left button after hitting enter state
                this->mLeftButtonPressed = false;
                break;
            case DebounceState::ENTER_TO_RIGHT_BUTTON:
                this->mDebounceState = DebounceState::NO_TO_LEFT_BUTTON;
                // Delay left button pressed for debounce count
                this->mCurrentDebouceCount = this->mDebounceCount;
                 this->mLeftButtonPressed = false;
                break;
        }
    }
    // Button state is left
    else if (!this->mLeftButtonPressed && this->mRightButtonPressed) 
    {
        switch (this->mDebounceState) {
            case DebounceState::NO_BUTTON_PRESSED:
                this->mDebounceState = DebounceState::NO_TO_RIGHT_BUTTON;
                // Delay left button pressed for debounce count
                this->mCurrentDebouceCount = this->mDebounceCount;
                this->mRightButtonPressed = false;
                break;
            case DebounceState::NO_TO_LEFT_BUTTON:
                this->mDebounceState = DebounceState::NO_TO_RIGHT_BUTTON;
                // Delay left button pressed for debounce count
                this->mCurrentDebouceCount = this->mDebounceCount;
                this->mLeftButtonPressed = true;
                this->mRightButtonPressed = false;
                 break;
            case DebounceState::NO_TO_RIGHT_BUTTON:
                // Send right button pressed then start debounce count for left
                if (this->mCurrentDebouceCount) { this->mCurrentDebouceCount--; }
                if (this->mCurrentDebouceCount) { this->mLeftButtonPressed = false; }
                break;
            case DebounceState::ENTER_BUTTON:
                this->mDebounceState = DebounceState::ENTER_TO_RIGHT_BUTTON;
                // Hide the left button after hitting enter state
                this->mRightButtonPressed = false;
                break;
            case DebounceState::ENTER_TO_LEFT_BUTTON:
                this->mDebounceState = DebounceState::NO_TO_RIGHT_BUTTON;
                // Delay right button for debounce count
                this->mCurrentDebouceCount = this->mDebounceCount;
                this->mRightButtonPressed = false;
                break;
            case DebounceState::ENTER_TO_RIGHT_BUTTON:
                // Hide the right button
                this->mRightButtonPressed = false;
                break;
        }
    }
}