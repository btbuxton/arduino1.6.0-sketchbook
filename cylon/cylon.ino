#include <Rainbowduino.h>

class Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;

  public:
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color* setPixel(unsigned char x, unsigned char y);
    void darker();
    Color* set(unsigned char r, unsigned char g, unsigned char b);
};

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
  this->set(r,g,b);
}

Color* Color::setPixel(unsigned char x, unsigned char y) {
  Rb.setPixelXY(x, y, r, g, b);
  return this;
}

void Color::darker() {
  r = r >> 1;
  g = g >> 2;
  b = b >> 1;
}

Color* Color::set(unsigned char r, unsigned char g, unsigned char b) {
  this->r = r;
  this->g = g;
  this->b = b;
  return this;
}

Color **GRID;

void setup() {
  Rb.init();
  randomSeed(analogRead(0));
  GRID = new Color*[64];
  for (int i=0; i < 64; i++)
    GRID[i]=new Color(0,0,0);
}

void darker() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      GRID[y*8 + x]->darker();
      GRID[y*8 + x]->setPixel(x, y);
    }
  }
}

void draw_line(int y, unsigned char r, unsigned char g, unsigned b) {
  for (int x = 0; x < 8; x++) {
    GRID[y*8 + x]->set(r,g,b);
    GRID[y*8 + x]->setPixel(x, y);
  }
}

void loop() {
  wander();
}

void wander() {
  static int x = random(0,8);
  static int y = random(0,8);
  GRID[y*8 + x]->set(0,255,255)->setPixel(x,y);
  darker();
  int dir_x = random(-1,2);
  int dir_y = random(-1,2);
  x += dir_x;
  y += dir_y;
  x = (x < 0) ? 0 : x;
  y = (y < 0) ? 0 : y;
  x = (x > 7) ? 7 : x;
  y = (y > 7) ? 7 : y;
  delay(100);
}

void dots() {
  int x = random(0,8);
  int y = random(0,8);
  GRID[y*8 + x]->set(0,255,255)->setPixel(x,y);
  darker();
  delay(100);
  
}
void lines() {
  int init_wait=100;
  int wait = init_wait;
  for (int y = 0; y < 8; y++) {
    darker();
    draw_line(y,255,0,0);
    delay(wait);
    //wait += init_wait / 4;
  }
  for (int y = 7; y >= 0; y--) {
    darker();
    draw_line(y,255,0,0);
    //wait -= init_wait / 4;
    delay(wait);
  }
}
