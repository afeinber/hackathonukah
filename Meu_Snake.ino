#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 7
#define HEIGHT 16
#define WIDTH 16
#define BLUE 0x001F

HardwareSerial Uart = HardwareSerial();

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

struct point
{
  int x;
  int y;
};
typedef struct point Point;

Point loc;
Point vel;
Point food;
int snakeSize;
Point tail[30];
int incomingByte;
int z;
boolean game = false;
boolean gameover = false;
  
void setup() {
  Uart.begin(115200);
  //Uart.setTimeout(100);
  Serial.begin(9600);
  z = -15;
  snakeSize = 1;
  loc.x = 8;
  loc.y = 8;
  vel.x = 1;
  vel.y = 0;
  game = false;
  food.x = 4;
  food.y = 5;
  matrix.begin();
  matrix.setBrightness(20);
  clrScreen();
  matrix.show();
}

void loop() {
  if(Uart.available() > 0) {
    incomingByte = Uart.read();
    if(incomingByte == 120) {
      game = !game;
    } else if(incomingByte == 119) {
      turn('U');
    } else if(incomingByte == 97) {
      turn('R');
    } else if(incomingByte == 115) {
      turn('D');
    } else if(incomingByte == 100) {
      turn('L');
    }
  }
  if(!game) {
    delay(100);
    writeSnake();
  }
  if(game) {
    delay(400);
    clrScreen();
    if(loc.x == food.x && loc.y == food.y) {
      eatFood();
    }
    for(int i=snakeSize-1;i>0;i--) {
      tail[i].x = tail[i-1].x;
      tail[i].y = tail[i-1].y;
    }
    tail[0].x = loc.x;
    tail[0].y = loc.y;
    loc.x += vel.x;
    loc.y += vel.y;
    checkWall();
    showFood();
    showSnake();
    matrix.show();
  }
}

void showSnake() {
    matrix.drawPixel(loc.x,loc.y, drawRGB24toRGB565(0,0,255));
    for(int i=0;i<snakeSize;i++) {
        matrix.drawPixel(tail[i].x,tail[i].y,drawRGB24toRGB565(random(50,256),random(50,256),random(50,256)));
    }
}

void showFood() {
    matrix.drawPixel(food.x,food.y, drawRGB24toRGB565(255,0,0));
}

uint16_t drawRGB24toRGB565(byte r, byte g, byte b) {
  return ((r/8) << 11) | ((g / 4) << 5) | (b / 8);
}

void clrScreen() {
  matrix.fillScreen(0);
}

void eatFood() {
  snakeSize++;
  food.x = random(0,16);
  food.y = random(0,16);
}

void turn(char dir) {
  switch(dir) {
    case 'U':
      vel.x = 0;
      vel.y = 1;
      break;
    case 'D':
      vel.x = 0;
      vel.y = -1;
      break;
    case 'L':
      vel.x = -1;
      vel.y = 0;
      break;
    case 'R':
      vel.x = 1;
      vel.y = 0;
      break;
  }
}

void checkWall() {
  if(loc.x < 0 || loc.x > 15 || loc.y < 0 || loc.y > 15) {
    delay(100);
    setup();
  }
}


void writeSnake() {
  clrScreen();
  matrix.drawPixel(z+15,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+14,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+13,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+15,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+15,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+14,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+13,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+13,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+13,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+14,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+15,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+15,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+11,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+11,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+11,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+11,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+11,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+10,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+9,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+8,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+8,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+8,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+8,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+8,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+5,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+6,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+6,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+6,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+6,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+3,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+3,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+3,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+3,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+5,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+4,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+4,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+1,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+1,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+1,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+1,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z+1,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-1,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-1,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-2,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-2,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-4,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-4,10,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-4,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-4,8,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-4,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-5,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-6,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-7,11,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-5,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-6,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-7,7,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-5,9,drawRGB24toRGB565(0,255,0));
  matrix.drawPixel(z-6,9,drawRGB24toRGB565(0,255,0));
  
  z++;
  if(z > 24) {
    z = -15;
  }
  matrix.show();
}
