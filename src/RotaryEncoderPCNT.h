#ifndef ROTARY_ENCODER_PCNT_H
#define ROTARY_ENCODER_PCNT_H

#include "driver/pulse_cnt.h"

#define START_POS_DEFAULT 0
#define GLITCH_NS_DEFAULT 1000

class RotaryEncoderPCNT {
  public:
    RotaryEncoderPCNT(int a, int b, int start_pos, uint16_t glitch_ns);
    RotaryEncoderPCNT(int a, int b, int start_pos);
    RotaryEncoderPCNT(int a, int b);
    ~RotaryEncoderPCNT();
    int  position();
    void setPosition(int pos);
    void zero();

  private:
    void install(int a, int b, int start_pos, uint16_t glitch_ns);

    pcnt_unit_handle_t unit;
    pcnt_channel_handle_t chan_a;
    pcnt_channel_handle_t chan_b;
    uint8_t pin_a;
    uint8_t pin_b;
    int count = 0;
    int offset = 0;
    int16_t low_limit = INT16_MIN;
    int16_t high_limit = INT16_MAX;
};
#endif
