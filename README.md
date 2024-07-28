# RotaryEncoderPCNT

This is a 2-channel rotary (quadrature) encoder implementation, for the ESP32, on the Arduino platform. It uses the ESP32's built in pulse counter (PCNT) peripheral.

Simply create a new `RotaryEncoderPCNT` object with the encoder's A and B pins, then call `.position()` to return the current position. The PCNT unit is set up to keep the encoder object updated in the background, handling interrupts, internal counter overflow, etc. for you.

Note: `.position()` returns a signed 32-bit integer. If you expect to overflow that, you need to handle it.

### Compatibility
- Requires Arduino ESP32 Core 3.0 or higher
- Incompatible with ESP32-C2 and ESP32-C3, as they don't have PCNT units.

### Most Basic Example
```
#include <RotaryEncoderPCNT.h>

RotaryEncoderPCNT encoder(25, 12);

void setup() {
  Serial.begin(115200);
}

void loop(){
  Serial.println(encoder.position());
  delay(200);
}
```
