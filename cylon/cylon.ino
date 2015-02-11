#include <Rainbowduino.h>

void setup() {
  Rb.init();

}

void draw_line(int y, int r, int g, int b) {
  for (int x=0; x < 8; x++) {
    Rb.setPixelXY(x,y,r,g,b);
  }
}

void loop() {
  for (int y=0; y < 8; y++) {
    if (y == 0) {
      draw_line(7,0,0,0);
    } else {
      draw_line(y-1,0,0,0);
    }
    draw_line(y,255,0,0);
    delay(25);
  }

}
