# RotaryEncoderPCNT

This is a 2-channel rotary (quadrature) encoder implementation, for the ESP32, on the Arduino platform. It uses the ESP32's built in pulse counter (PCNT) peripheral. The PCNT unit is set up to keep the encoder object updated in the background, handling interrupts, internal counter overflow, etc. for you.

### Compatibility
- Requires Arduino ESP32 Core 3.0 or higher
- Incompatible with ESP32-C2 and ESP32-C3, as they don't have PCNT units.

### Most Basic Example
```C++
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

Note: `.position()` returns a signed 32-bit integer. If you expect to overflow that, you need to handle it.

See included examples for more.
