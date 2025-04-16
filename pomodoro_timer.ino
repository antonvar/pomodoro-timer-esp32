#define BTN_PIN 12
#include "GyverButton.h"

GButton butt1(BTN_PIN);

#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

int minut = 0;
int sec = 0;
int tomat = 0;

bool status = false;
bool paused = false;

int workTime = 1; 
int chillTime = 1;

unsigned long timer;

void setup() {
Serial.begin(9600);

timer = millis();

oled.init();       
oled.clear();
oled.setScale(2);
oled.setCursorXY(25,0);
oled.print("Работа");
oled.setScale(1);
oled.setCursor(0,6);
oled.print(String(tomat) +"/12");

}
void loop() {
  butt1.tick();
  String minStr = (minut < 10) ? "0" + String(minut) : String(minut);
  String secStr = (sec < 10) ? "0" + String(sec) : String(sec);

  if (butt1.isClick()) Serial.println(paused = !paused);

  if (millis() - timer > 1000) {timer = millis(); sec = sec + 1;}

  if (sec > 59) {sec = 0; minut = minut + 1;}
          
  if (minut > workTime && status == false) {minut = 0; sec = 0; status = true; tomat = tomat + 1;
  oled.clear();
  oled.setScale(2);
  oled.setCursorXY(30,0);
  oled.print("Отдых");
  oled.setScale(1);
  oled.setCursor(0,6);
  oled.print(String(tomat) +"/12");
  }

  if (minut > chillTime && status == true) {minut = 0; sec = 0; status = false;
  oled.clear();
  oled.setScale(2);
  oled.setCursorXY(25,0);
  oled.print("Работа");
  oled.setScale(1);
  oled.setCursor(0,6);
  oled.print(String(tomat) +"/12");
  }

   // вывод на дисплей
  oled.setScale(3);
  oled.setCursorXY(20, 16);
  oled.print(String(minStr) + ":" + String(secStr));
}