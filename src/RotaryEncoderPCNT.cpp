#include "RotaryEncoderPCNT.h"

RotaryEncoderPCNT::RotaryEncoderPCNT(int a, int b, int start_pos, uint16_t glitch_ns){
  install(a, b, start_pos, glitch_ns);
}

RotaryEncoderPCNT::RotaryEncoderPCNT(int a, int b, int start_pos){
  install(a, b, start_pos, GLITCH_NS_DEFAULT);
}

RotaryEncoderPCNT::RotaryEncoderPCNT(int a, int b){
  install(a, b, START_POS_DEFAULT, GLITCH_NS_DEFAULT);
}

void RotaryEncoderPCNT::install(int a, int b, int start_pos, uint16_t glitch_ns){
  offset = start_pos;
  pin_a = a;
  pin_b = b;

  // Unit config
  pcnt_unit_config_t unit_config = {
      .low_limit = low_limit,
      .high_limit = high_limit,
  };
  unit_config.flags.accum_count = true;

  // Create unit
  ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &unit));

  // Set watch points at low and high limits to auto-accumulate overflows.
  pcnt_unit_add_watch_point(unit, low_limit);
  pcnt_unit_add_watch_point(unit, high_limit);

  // Glitch filter setup
  pcnt_glitch_filter_config_t filter_config = {
      .max_glitch_ns = glitch_ns,
  };
  ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(unit, &filter_config));

  // Channel A setup
  pcnt_chan_config_t chan_a_config = {
      .edge_gpio_num = pin_a,
      .level_gpio_num = pin_b,
  };
  ESP_ERROR_CHECK(pcnt_new_channel(unit, &chan_a_config, &chan_a));

  // Channel B setup
  pcnt_chan_config_t chan_b_config = {
      .edge_gpio_num = pin_b,
      .level_gpio_num = pin_a,
  };
  ESP_ERROR_CHECK(pcnt_new_channel(unit, &chan_b_config, &chan_b));

  // Set edge and level actions for both channels
  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
  ESP_ERROR_CHECK(pcnt_channel_set_level_action(chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
  ESP_ERROR_CHECK(pcnt_channel_set_level_action(chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

  // Enable, clear and start the PCNT unit.
  ESP_ERROR_CHECK(pcnt_unit_enable(unit));
  ESP_ERROR_CHECK(pcnt_unit_clear_count(unit));
  ESP_ERROR_CHECK(pcnt_unit_start(unit));
}

RotaryEncoderPCNT::~RotaryEncoderPCNT(){
    // Free PCNT resources when destroyed.
    pcnt_unit_disable(unit);
    pcnt_del_channel(chan_a);
    pcnt_del_channel(chan_b);
    pcnt_del_unit(unit);
}

int RotaryEncoderPCNT::position(){
  pcnt_unit_get_count(unit, &count);
  return (count + offset);
}

void RotaryEncoderPCNT::setPosition(int pos){
  offset = pos;
  pcnt_unit_get_count(unit, &count);
  zero();
}

void RotaryEncoderPCNT::zero(){
  pcnt_unit_clear_count(unit);
}
