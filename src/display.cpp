#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "variables.h"
#import "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Display::initialize() {
  //Display starten
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
}

void Display::testText() {
  //Display Text anzeigen
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Hello, World!");
  display.display();
}