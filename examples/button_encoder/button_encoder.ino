#include <ButtonEncoder.h>

/**
 * Basic Button Encoder using ..
 *
 * Digital Pin 16 as Left Button
 * Digital Pin 14 as Right Button
 * Digital Pin 15 as Enter Button
 */
static ButtonEncoder be(16, 14, 15);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  be.readEncoder();
  if (be.keyPressed()) {
    Serial.println("KeyPressed");
    if (be.lastKeyPressed() == Encoder::EncoderKey::ENCODER_LEFT) {
      Serial.println("LEFT");
    }
    if (be.lastKeyPressed() == Encoder::EncoderKey::ENCODER_RIGHT) {
      Serial.println("RIGHT");
    }
        if (be.lastKeyPressed() == Encoder::EncoderKey::ENCODER_ENTER) {
      Serial.println("ENTER");
    }
  }
  delay(60);
}
