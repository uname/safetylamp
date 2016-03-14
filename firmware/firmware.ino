#include <Adafruit_NeoPixel.h>

#define PIN 3
#define NUM 9
#define BRIGHTNESS 255
#define SET_LAMP_COLOR(color) for(int j = 0; j < NUM; j++) lamp.setPixelColor(j, color)

Adafruit_NeoPixel lamp = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
typedef struct
{
    uint8_t  brightness; // [0, 255]
    uint32_t color;      //
    uint32_t frequency;  // HZ
    uint32_t duration;   // S
} LampLightType;

LampLightType lampLights[] = {
    {0xff, 0xffff0000, 6, 5},
    {0xff, 0xff0000ff, 10, 2},
} ;

void setup()
{
    lamp.begin();
}

void loop()
{
    const int count = sizeof(lampLights) / sizeof(lampLights[0]);
    for(int i = 0; i < 2; i++) {
        if(lampLights[i].frequency < 1) {
            lampLights[i].frequency = 1;
        }
        uint32_t ms = 1000 / lampLights[i].frequency;
        SET_LAMP_COLOR(lampLights[i].color);
        uint32_t t0 = millis();
        while(1) {
            uint32_t t1 = millis();
            if(t1 - t0 > lampLights[i].duration * 1000) {
                break;
            }
            lamp.setBrightness(BRIGHTNESS);
            SET_LAMP_COLOR(lampLights[i].color);
            lamp.show();
            delay(ms);
            lamp.setBrightness(0);
            lamp.show();
            delay(ms);
        }
    }
}



