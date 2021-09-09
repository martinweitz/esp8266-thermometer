/**
  Thermometer firmware for NodeMCU (ESP8266), 
  Dallas DS18B20 temperature sensor and TFT Display

  External dependencies:
     "OneWire" by Paul Stoffregen
     "DallasTemperature" by Miles Burton
     "Adafruit_GFX" and "Adafruit_ST7735" by Adafruit
     
  Written by Martin Weitz
    
*/
/* ---------------------- General config -------------------------------- */
//#define     SERIAL_BAUD_RATE    115200

/* ---------------------- Hardware-specific config ---------------------- */
#define oneWireBus     D1 // define Pin D1 as sensor bus
#define TFT_CS         D3 // define Pin D3 as Chipselect
#define TFT_RST        D4 // define Pin D4 as Reset
#define TFT_DC         D8 // define Pin D8 as DC

/* ------------------------- TFT-specific config ------------------------ */
#define ROTATION_NO 0
#define ROTATION_90 1
#define ROTATION_180 2
#define ROTATION_270 3

/*--------------------------- Libraries ----------------------------------*/
#include <Arduino.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <DallasTemperature.h>
#include <Base64.h>
#include <OneWire.h>

/*--------------------------- Global Variables ---------------------------*/
char temperaturStr[6];
float lastTemperature=0;

/*--------------------------- Function Signatures ------------------------*/
void tftDrawFrame();
void tftDrawLabels();
float getTemperatur();
void showTemperatur(float temperatur);

/*--------------------------- Instantiate Global Objects -----------------*/
// Display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// OneWire Bus
OneWire oneWire(oneWireBus);

// Temperature Sensor
DallasTemperature sensors(&oneWire);

/*--------------------------- Program ------------------------------------*/

void setup() 
{
  // init sensors on bus
  sensors.begin();

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

/*--------------------------- Functions ------------------------------------*/

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
