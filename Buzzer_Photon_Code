// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

#define PIXEL_PIN D5
#define PIXEL_COUNT 3
#define PIXEL_TYPE WS2811
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE); // create strip to set color


int speakerPin = D0;
bool alarmSwitch = false;

// twinkle star here
int melody[] = {
        146.83,
        146.83,
        220.00,
        220.00,
        246.94,
        246.94,
        220.00,
        
        196.00,
        196.00,
        185.00,
        185.00,
        164.81,
        164.81,
        146.83,
        
        220.00,
        220.00,
        196.00,
        196.00,
        185.00,
        185.00,
        164.81,
        
        220.00,
        220.00,
        196.00,
        196.00,
        185.00,
        185.00,
        164.81,
        
        146.83,
        146.83,
        220.00,
        220.00,
        246.94,
        246.94,
        220.00,
        
        196.00,
        196.00,
        185.00,
        185.00,
        164.81,
        164.81,
        146.83
    };
    
    
// note durations 
int noteDurations[] = {
        4,
        4,
        4,
        4,
        4,
        4,
        2,
        
        4,
        4,
        4,
        4,
        4,
        4,
        2,
        
        4,
        4,
        4,
        4,
        4,
        4,
        2,
        
        4,
        4,
        4,
        4,
        4,
        4,
        2,
        
        4,
        4,
        4,
        4,
        4,
        4,
        2,
        
        4,
        4,
        4,
        4,
        4,
        4,
        2,
    };


bool buttonNow = FALSE;
bool buttonLast = FALSE;

int PixelColorBlue = strip.Color( 0, 0, 128);
int PixelColorRed  = strip.Color( 80, 0, 4);
int PixelColorGold = strip.Color( 60, 50, 5);
int pink           = strip.Color(255,105,180);
int purple         = strip.Color(128,0,128);
int yellow         = strip.Color(255,255,0);

int colorArray[] = {PixelColorBlue, PixelColorRed, PixelColorGold, pink, purple, yellow};

void blinkLed()
{
        strip.setPixelColor(0, PixelColorBlue);
        strip.show();
        delay(1000);
        strip.setPixelColor(1, PixelColorGold);
        strip.show();
        delay(1000);
        strip.setPixelColor(2, PixelColorRed);
        strip.show();
        delay(1000);
        
        strip.setPixelColor(0, PixelColorRed);
        strip.show();
        delay(1000);
        strip.setPixelColor(1, PixelColorBlue);
        strip.show();
        delay(1000);
        strip.setPixelColor(2, PixelColorGold);
        strip.show();
        delay(1000);
}


int step = 0;
int light = 0;
void playSong(int step)
{
    int noteDuration = 1500 / noteDurations[step];
    tone(speakerPin, melody[step], noteDuration);
    
    strip.setPixelColor(light, colorArray[random(6)]);
    strip.show();
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
        
    noTone(speakerPin);
}


void correct(const char *event, const char *data)
{
    
    alarmSwitch = false;
    Serial.println("false");
    Particle.unsubscribe();
}

void alarm(const char *event, const char *data)
{
    alarmSwitch = true;
    Particle.unsubscribe();
    Particle.subscribe("EE1301_Alarm_Pattern_Correct", correct, "400034001547343339383037");
    Serial.println("true");
}

int songLength = arraySize(melody);

void setup() 
{
    Serial.begin(9600);
    strip.begin();
    randomSeed(Time.now());
  Particle.subscribe("EE1301_Alarm", alarm, "400034001547343339383037");
   
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() 
{
    if (alarmSwitch == true)
    {
        
        playSong(step);
        step++;
        
        light++;

    }
    else
    {
        // song
        step = 0; // reset the song
    }
    if (step >= songLength)
    {
        step = 0;
    }
    
    if (light >= 3)
        light = 0;
}
