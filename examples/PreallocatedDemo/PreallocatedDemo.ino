#include <RotaryEncoderPCNT.h>

// Allocate the encoder up front. This doesn't set pins or start it.
RotaryEncoderPCNT encoder;
int old_position;
int position;

void setup() {
  Serial.begin(115200);

  // Now set pins and start the encoder.
  encoder.pin_a = 25;
  encoder.pin_b = 12;
  encoder.init();

  // Show initial position.
  old_position = encoder.position();
  Serial.println(old_position);
}

void loop() {
  // Show position when it changes.
  position = encoder.position();
  if(position != old_position){
    Serial.println(position);
    old_position = position;
  }
  delay(5);
}
