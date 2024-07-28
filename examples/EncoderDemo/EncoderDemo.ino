#include <RotaryEncoderPCNT.h>

// Constructor args are: pinA/Clock, pinB/Data, start position, glitch filter time in ns.
// Start position and filter time are optional. Defaults are 0 and 1000ns respectively.
//
// RotaryEncoderPCNT encoder(25, 12, 0, 1000);
// RotaryEncoderPCNT encoder(25, 12, 0);
RotaryEncoderPCNT encoder(25, 12);

int old_position;
int position;

void setup() {
  Serial.begin(115200);

  // Change position after initialization.
  // encoder.setPosition(128);

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
