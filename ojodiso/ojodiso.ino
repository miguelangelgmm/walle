#include "Adafruit_GC9A01A.h"

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST -1 

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.setRotation(3); 
  tft.fillScreen(GC9A01A_BLACK); 
  drawEye(120, 120, 120, 25); 
}

void loop() {
  // No hay animaciones en el loop
}

void drawEye(int x, int y, int outerRadius, int pupilRadius) {
  // Dibujar borde del ojo (en azul)
  for (int r = outerRadius; r > outerRadius - 10; r--) {
    uint16_t color = tft.color565(0, 0, map(r, outerRadius, outerRadius - 10, 100, 255));
    tft.fillCircle(x, y, r, color);
  }

  // Dibujar iris con un degradado azul cian
  for (int r = outerRadius - 10; r > pupilRadius; r--) {
    uint16_t color = tft.color565(0, map(r, pupilRadius, outerRadius, 50, 150), map(r, pupilRadius, outerRadius, 100, 255)); // Degradado azul cian
    tft.fillCircle(x, y, r, color);
  }

  // Dibuja la pupila (parte negra del ojo)
  tft.fillCircle(x, y, pupilRadius, GC9A01A_BLACK);

  // Dibujar reflejos en diferentes tonos de azul y blanco
  drawReflection(x - outerRadius / 3, y - outerRadius / 3, outerRadius / 10, 200, 225, 255); // Azul muy claro
  drawReflection(x + outerRadius / 4, y - outerRadius / 4, outerRadius / 12, 150, 200, 255); // Azul claro
  drawReflection(x - outerRadius / 4, y + outerRadius / 4, outerRadius / 14, 100, 150, 255);  // Azul medio
  drawReflection(x + outerRadius / 8, y + outerRadius / 8, outerRadius / 20, 255, 255, 255);  // Pequeño reflejo blanco
}

void drawReflection(int x, int y, int radius, int r, int g, int b) {
  uint16_t color = tft.color565(r, g, b);
  tft.fillCircle(x, y, radius, color);
}


//Rojo 3.3V, verde GND, azulblanco 13 SCL, Naranja,Manguera de 4 SDA 11, Azul CS 10, Naranja blanco 9 DC 
