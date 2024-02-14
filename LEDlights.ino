#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 2
#define MAX_BRIGHTNESS 175
#define MIN_BRIGHTNESS 50
#define HUE 20
#define STEP 3

// Globals
CRGB leds[NUM_LEDS];
CHSV colorOrange1(HUE, 255, MAX_BRIGHTNESS);
CHSV colorOrange2(HUE, 255, MIN_BRIGHTNESS);
bool flag1 = true;
bool flag2 = true;


// Sets the settings for beginning (initialization)
void setup() 
{
  // Declare the LED chip, pin, the array with the sizeof array
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
}


// Function allows individual LEDs to adjust brightness
void setBrightness1(uint8_t step)
{
  uint8_t brightness = colorOrange1.v;
  if(brightness >= MAX_BRIGHTNESS || !(flag1))
  {
    flag1 = false;
    colorOrange1.v = brightness - step;
  }
  if(brightness <= MIN_BRIGHTNESS || flag1)
  {
    flag1 = true;
    colorOrange1.v = brightness + step;
  }
}

void setBrightness2(uint8_t step)
{
  uint8_t brightness = colorOrange2.v;
  if(brightness >= MAX_BRIGHTNESS || !(flag2))
  {
    flag2 = false;
    colorOrange2.v = brightness - step;
  }
  if(brightness <= MIN_BRIGHTNESS || flag2)
  {
    flag2 = true;
    colorOrange2.v = brightness + step;
  }
}

// Function sets all LEDs brightness
void setIncDecBrightness(uint8_t lum_level)
{
  uint8_t brightness = FastLED.getBrightness();
  if(brightness >= MAX_BRIGHTNESS || !(flag1))
  {
    flag1 = false;
    FastLED.setBrightness(brightness - lum_level);
  }
  if(brightness <= MIN_BRIGHTNESS || flag1)
  {
    flag1 = true;
    FastLED.setBrightness(brightness + lum_level);
  }
}

void setOrangeBrightnessMode()
{
  setIncDecBrightness(1);
  for(int led_index = 1; led_index < NUM_LEDS; led_index++)
  {
    leds[led_index] = CRGB::OrangeRed;
  }
  FastLED.show();
  delay(10);
}

void setOrangeAlternateMode()
{
  for(int led_index = 1; led_index < NUM_LEDS; led_index += 2)
  {
    leds[led_index] = CRGB::OrangeRed;
    leds[led_index - 1] = CRGB::Black;
  }
  FastLED.show();
  delay(2000);
  for(int led_index = 1; led_index < NUM_LEDS; led_index += 2)
  {
    leds[led_index] = CRGB::Black;
    leds[led_index - 1] = CRGB::OrangeRed;
  }
  FastLED.show();
  delay(2000);
}

// Alternates and adjusts brighntess like twinkling stars
void setTwinkle()
{
  setBrightness1(STEP);
  for(int led_index = 1; led_index < NUM_LEDS; led_index += 2)
  {
    leds[led_index] = colorOrange1;
    leds[led_index].fadeLightBy(64);
  }
  FastLED.show();
  delay(10);
  setBrightness2(STEP);
  for(int led_index = 1; led_index < NUM_LEDS; led_index += 2)
  {
    leds[led_index - 1] = colorOrange2;
    leds[led_index - 1].fadeLightBy(64);
  }
  FastLED.show();
  delay(10);
}

void loop() 
{
  //setOrangeBrightnessMode();
  //setOrangeAlternateMode();
  setTwinkle();
}






