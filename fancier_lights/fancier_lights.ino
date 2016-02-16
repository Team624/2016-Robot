#include <Adafruit_NeoPixel.h>
#include "Wire.h"

#define PIN 5
#define PINZ 2

#define ROBOT_STATE_PIN 12
#define ROBOT_STATE_PIN_TWO 22
#define ROBOT_STATE_PIN_THREE 28

Adafruit_NeoPixel strip = Adafruit_NeoPixel(31, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripz = Adafruit_NeoPixel(31, PINZ, NEO_GRB + NEO_KHZ800);

#include "utilities.h"

void setup() 
{
  pinMode(PIN, OUTPUT);
  pinMode(PINZ, OUTPUT);
  
  strip.begin();
  strip.show();
  
  stripz.begin();
  stripz.show();
  Serial.begin(9600);
}

#define STATE_TELEOP 0b000
#define STATE_AUTONOMOUS 0b001
#define STATE_SHOOT 0b010
#define STATE_BROWNOUT 0b100
#define STATE_LOST_COMMS 0b101
#define STATE_DISABLED 0b111

bool first_loop = false;
uint8_t robot_state, old_state;

void loop() 
{
  old_state = robot_state;
  
  bool state_pin1 = digitalRead(ROBOT_STATE_PIN);
  bool state_pin2 = digitalRead(ROBOT_STATE_PIN_TWO);
  bool state_pin3 = digitalRead(ROBOT_STATE_PIN_THREE);
  
  Serial.println();
  Serial.print(state_pin3);
  Serial.print(state_pin2);
  Serial.print(state_pin1);
  
  robot_state = ((state_pin3 << 2) & 0b100) | ((state_pin2 << 1) & 0b10) | ((state_pin1) & 0b1);

  Serial.println();
  Serial.println(robot_state);
  
  if(robot_state != old_state)
  {
    first_loop = false;
  }
  
  if(robot_state == STATE_TELEOP || robot_state == STATE_SHOOT)
  {
    statusLights();
  }
  else if(robot_state == STATE_AUTONOMOUS)
  {
  }  
  else if(robot_state == STATE_BROWNOUT)
  {
    fillStrip(strip.Color(139,69,19), 255);
    fillStripZ(stripz.Color(139,69,19), 255);
  }
  else if(robot_state == STATE_LOST_COMMS)
  {
    fillStrip(strip.Color(255,0,0), 255);
    fillStripZ(stripz.Color(255,0,0), 255); 
  }
//31 LEDs on the 20 in. strip
  strip.show();
  stripz.show();
}

void statusLight()
{
  uint8_t blue = strip.Color(0,0,255);
  uint8_t green = strip.Color(#06F000);
  uint8_t red = strip.Color(255,0,0);
  uint8_t yellow = strip.Color(255,255,0);
  
  
}

