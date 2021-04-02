#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
// Libraries for DS18B20
#include <DallasTemperature.h>
#include <Base64.h>
#include <OneWire.h>

#define TFT_CS         D3 // define Pin D3 as Chipselect
#define TFT_RST        D4 // define Pin D4 as Reset
#define TFT_DC         D8 // define Pin D8 as DC

// create instance of Adafruit_ST7735 class
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define ROTATION_NO 0
#define ROTATION_90 1
#define ROTATION_180 2
#define ROTATION_270 3

#define oneWireBus D1   //Bestimmt Port an dem der Sensor angeschlossen ist

// create instance of OneWire class
OneWire oneWire(oneWireBus);

// create instance of DallasTemperature class
DallasTemperature sensors(&oneWire);

char temperaturStr[6];
float lastTemperature=0;


// forward declarations of functions
void tftDrawFrame();
void tftDrawLabels();

float getTemperatur(); // Deklaration getTemperatur
void showTemperatur(float temperatur);


void setup() {
 
sensors.begin();
//Serial.begin(115200);

 // Use this initializer if using a 1.8" TFT screen:
tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
tft.setRotation(ROTATION_270);

tftDrawFrame();
tftDrawLabels();
}

void loop()
{
float temperatur = getTemperatur();

if (lastTemperature!=temperatur) 
    {
    showTemperatur(temperatur);
    lastTemperature=temperatur;
    }
}

void tftDrawFrame() 
{
    tft.fillScreen(ST77XX_BLACK);
    tft.drawRoundRect(1, 0, tft.width()-1, 30, 10, ST77XX_BLUE);
    tft.drawRoundRect(1, 35, tft.width()-1, 90, 10, ST77XX_GREEN);
}

void tftDrawLabels()
{
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(15,8);
    tft.setTextSize(2);
    tft.print("Thermometer");
    tft.setCursor(10,40);
    tft.setTextSize(1);
    tft.print("Temperatur in ");
    tft.setTextSize(0);
    tft.print("O");
    tft.setTextSize(2);
    tft.print("C");
}

float getTemperatur()
{
    float temp =0;
do {
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    Serial.print(temp);
    delay(5000);
} while (temp == 85.0 || temp == (-127.0));

return temp;
}

void showTemperatur(float temperatur)
{
    dtostrf(temperatur, 2, 1, temperaturStr);
    tft.setTextSize(6);
    tft.setTextColor(ST77XX_WHITE, ST7735_BLACK);
    tft.setCursor(12,70);
    tft.print(temperaturStr);
}
