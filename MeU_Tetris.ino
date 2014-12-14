#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 7
#define HEIGHT 16
#define WIDTH 16

struct point
{
  int x;
  int y;
};
typedef struct point Point;

struct block
{
  Point shape[4];
};
typedef struct block Block;

HardwareSerial Uart = HardwareSerial();

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

Block i_shape;
Block i_flip;
Block j_shape;
Block j_flip_left;
Block j_flip_right;
Block j_flip_down;
Block l_shape;
Block o_shape;
Block z_shape;
Block t_shape;
Block s_shape;
Block current;
Block pickRandomBlock();
int x = 8;
int y = 16;
Point taken[256];
int n;
int m;
int incomingByte;
boolean game;

void setup() {
  Uart.begin(115200);
  Serial.begin(9600);
  blockDef();
  randomSeed(millis());
  matrix.begin();
  matrix.setBrightness(20);
  matrix.fillScreen(0);
  matrix.show();
  n = 0;
  m = 0;
  current = pickRandomBlock();
  game = false;
}

void loop() {
  if(Uart.available() > 0) {
    incomingByte = Uart.read();
    if(incomingByte == 97) {
      x++;
      game = true;
    } else if(incomingByte == 100) {
      x--;
      game = true;
    } else if(incomingByte == 119) {
      flip();
    } else if(incomingByte == 115) {
      flip();
    }
  }
  if(game) {
    matrix.fillScreen(0);
    delay(500);
    if(y==0) {
      for(int i=0;i<4;i++) {
        taken[n].x = x + current.shape[i].x;
        taken[n].y = y + current.shape[i].y;
        n++;
      }
      current = pickRandomBlock();
      y = 16;
    }
    y--;
    for(int i=0;i<=n;i++) {
      if(y == taken[i].y && x + current.shape[i].x==taken[i].x) {
        for(int i=0;i<4;i++) {
          taken[n].x = x + current.shape[i].x;
          taken[n].y = (y+1) + current.shape[i].y;
          n++;
        }
        current = pickRandomBlock();
        y = 16;
        break;
      }
    }
    showCurrentBlock();
    showTakenBlocks();
    matrix.show();
  }
}

uint16_t drawRGB24toRGB565(byte r, byte g, byte b) {
  return ((r/8) << 11) | ((g / 4) << 5) | (b / 8);
}

void showCurrentBlock() {
  for(int i=0;i<4;i++) {
    matrix.drawPixel(x+current.shape[i].x,y+current.shape[i].y,drawRGB24toRGB565(0,0,255));
  }
}

void showTakenBlocks() {
  for(int i=0;i< n;i++) {
    matrix.drawPixel(taken[i].x,taken[i].y,drawRGB24toRGB565(255,0,0));
  }
}

void flip() {
  if(m==0) {
    current = i_flip;
    m++;
  } else if(m==1) {
    current = i_flip;
    m++;
  } else if(m==2) {
    current = j_flip_right;
    m++;
  } else if(m==3) {
    current = j_flip_down;
    m++;
  }
}

Block pickRandomBlock() {
  int num = random(0,7);
  switch(num) {
    case 0:
        return i_shape;
        break;
    case 1:
        return j_shape;
        break;
    case 2:
        return l_shape;
        break;
    case 3:
        return o_shape;
        break;
    case 4:
        return z_shape;
        break;
    case 5:
        return t_shape;
        break;
    case 6:
        return s_shape;
        break;
  }
}

void blockDef() {
  for(int i=0;i<4;i++) {
  i_shape.shape[i].x = 0;
  i_shape.shape[i].y = i;
}
for(int i=0;i<4;i++) {
  i_flip.shape[i].x=i;
  i_flip.shape[i].y = 0;
}
for(int i=0;i<3;i++) {
  j_shape.shape[i].x = 0;
  j_shape.shape[i].y = i;
}
j_shape.shape[3].x = 1;
j_shape.shape[3].y = 0;
for(int i=0;i<3;i++) {
  j_flip_right.shape[i].x=i;
  j_flip_right.shape[i].y=0;
}
j_flip_right.shape[3].x = 0;
j_flip_right.shape[3].y = 1;

for(int i=0;i<3;i++) {
  j_flip_left.shape[i].x=i;
  j_flip_left.shape[i].y=0;
}
j_flip_left.shape[3].x = 2;
j_flip_left.shape[3].y = -1;

for(int i=0;i<3;i++) {
  j_flip_down.shape[i].x=0;
  j_flip_down.shape[i].y=i;
}
j_flip_down.shape[3].x = 1;
j_flip_down.shape[3].y = 2;

for(int i=0;i<3;i++) {
  l_shape.shape[i].x = 0;
  l_shape.shape[i].y = i;
}
l_shape.shape[3].x = -1;
l_shape.shape[3].y = 0;

for(int i=0;i<2;i++) {
  o_shape.shape[i].x = 0;
  o_shape.shape[i].y = i;
}
o_shape.shape[2].x = 1;
o_shape.shape[2].y = 0;
o_shape.shape[3].x = 1;
o_shape.shape[3].y = 1;

for(int i=0;i<2;i++) {
  z_shape.shape[i].x = 0;
  z_shape.shape[i].y = i;
}
z_shape.shape[2].x = -1;
z_shape.shape[2].y = 0;
z_shape.shape[3].x = 1;
z_shape.shape[3].y = 1;

for(int i=0;i<2;i++) {
  t_shape.shape[i].x = 0;
  t_shape.shape[i].y = i;
}
t_shape.shape[2].x = -1;
t_shape.shape[2].y = 0;
t_shape.shape[3].x = 1;
t_shape.shape[3].y = 0;

for(int i=0;i<2;i++) {
  s_shape.shape[i].x = 0;
  s_shape.shape[i].y = i;
}
s_shape.shape[2].x = 1;
s_shape.shape[2].y = 0;
s_shape.shape[3].x = -1;
s_shape.shape[3].y = 1;
}
