#include <Arduino.h>
#include "config.h"
#include "crsf.h"
#include "crsf_protocol.h"
#include "halfduplex.h"
#include "uart.h"
#include "gpio.h"


rc_input_t rcInput;

void setup(){

  for (uint8_t i = 0; i < CRSF_MAX_CHANNEL; i++)
  {
    rcChannels[i] = RC_CHANNEL_MIN;
  }

  // uart debug
  dbout.begin(115200);
  delay(2000);
  elrs.begin(SERIAL_BAUDRATE, SERIAL_8N1, GPIO_PIN_RCSIGNAL_RX, GPIO_PIN_RCSIGNAL_TX, true, 500);
  dbout.write("starting mlrs\n");
  // digitalWrite(DIGITAL_PIN_LED, LOW); //LED ON
  delay(2000);

}
void loop(){

uint32_t currentMicros = micros();
if (currentMicros >= crsfTime)
  {
   gpioReadInputs(&rcInput);

   // send crsf channels packet
   crsfSendChannels(&rcInput);

   serialEvent();
   
  } 

}