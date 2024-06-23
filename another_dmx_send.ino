#include <dummy.h>
#include <Arduino.h>
#include <esp_dmx.h>
#include <ColorConverterLib.h>


int transmitPin = 14;
int receivePin = 27;
int enablePin = 21;

uint8_t i; 

dmx_port_t dmxPort = 1;

byte data[DMX_PACKET_SIZE];

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
double hue = 0.0;
double saturation = 1.0;
double value = 1.0;

unsigned long lastUpdate = millis();

void setup() {
  Serial.begin(115200);
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  dmx_driver_install(dmxPort, &config, DMX_INTR_FLAGS_DEFAULT);
  dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);
}

void loop() {
  
      hue = i / 255.0;
      RGBConverter::HsvToRgb(hue, saturation, value, r, g, b);
      data[1] = 255; 
      data[2] = r; 
      data[3] = g; 
      data[4] = b; 
      
      dmx_write(dmxPort, data, DMX_PACKET_SIZE);
      i++; 


    dmx_send(dmxPort, DMX_PACKET_SIZE);
    dmx_wait_sent(dmxPort, DMX_TIMEOUT_TICK);
}