#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735


#define TFT_CS         D3 // define Pin D3 as Chipselect
#define TFT_RST        D4 // define Pin D4 as Reset
#define TFT_DC         D8 // define Pin D8 as DC

// create instance of Adafruit_ST7735 class

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// forward declarations of functions
void tftPrintTest();
void tftDrawFrame();
void tftDrawLabels();


void setup() {
 
 // Use this initializer if using a 1.8" TFT screen:
tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

tftDrawFrame();
tftDrawLabels();
delay(1000);

}

void loop() {

delay(500);

}

void tftDrawFrame() 
{
tft.fillScreen(ST77XX_BLACK);
tft.drawRoundRect(1, 0, tft.width()-1, 30, 10, ST77XX_BLUE);
tft.drawRoundRect(1, 35, tft.width()-1, 90, 10, ST77XX_GREEN);
tft.drawRoundRect(1, 130, tft.width()-1, 30, 10, ST77XX_RED);
}

void tftDrawLabels()
{
tft.setTextColor(ST77XX_WHITE);
tft.setCursor(10,40);
tft.setTextSize(1);
tft.print("Temperatur in ");
tft.setTextSize(0);
tft.print("O");
tft.setTextSize(1);
tft.print("C");
}