#include "Encoder.h"

/**
 * @brief Returns true for the encoder key being pressed
 * 
 * @return true The lastKeyPressed represents the current encoder being pressed
 * @return false The encoder is no-longer being pressed
 */
bool Encoder::keyPressed() {
    return mKeyPressed;
}

/**
 * @brief Returns the lastKeyPressed of the encoder
 * 
 * @return EncoderKey 
 */
Encoder::EncoderKey Encoder::lastKeyPressed() {
    return mLastKeyPressed;
}