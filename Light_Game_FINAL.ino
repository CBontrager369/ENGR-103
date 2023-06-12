#include <Adafruit_CircuitPlayground.h>

volatile int level = 1;
int del = 100;
int start = 0;
int rightButton = 5;
volatile int rbutton = 0;
volatile bool rightFlag = 0;
volatile bool leftFlag = 0;
int leftButton = 4;
int lVal = 0;

void setup() 
{
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(rightButton), rightbutton, RISING);
  attachInterrupt(digitalPinToInterrupt(leftButton), leftbutton, RISING);
}

void loop() 
{
  // Level controls.
  if(level == 0)
  {
    level = 1;
  }
  
  // Buttons
  if (rightFlag)
  {
    delay(5);
    rbutton = 1;
    rightFlag = 0;
  }

  if (leftFlag)
  {
    delay(5);
    level = 1;
    leftFlag=0;
    delay(800);
  }

  // White and Green lights.
  CircuitPlayground.setPixelColor(lVal, 50, 50, 50);
  CircuitPlayground.setPixelColor(7, 0, 255, 0);
  delay(del-20*level);
  CircuitPlayground.setPixelColor(lVal, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 255, 0);
  delay(del-20*level);
  
  if(lVal < 10)
  {
    lVal++;   
  } else if (lVal = 10)
  {
    lVal = 0;
  }

  // Winning and loosing a level.
  if(rightFlag == 1 && lVal == 7)
  {
    CircuitPlayground.playTone(70, 400);
    CircuitPlayground.playTone(90, 100);
    CircuitPlayground.playTone(110, 200);
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500);
    level++;
  } else if(rightFlag == 1 && !(lVal == 7))
  {
    CircuitPlayground.playTone(70, 400);
    CircuitPlayground.playTone(60, 100);
    CircuitPlayground.playTone(50, 200);
    CircuitPlayground.setPixelColor(lVal, 50, 50, 50);
    CircuitPlayground.setPixelColor(7, 255, 0, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500);   
    CircuitPlayground.setPixelColor(7, 255, 0, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500); 
    CircuitPlayground.setPixelColor(7, 255, 0, 0);
    delay(500);
    CircuitPlayground.setPixelColor(7, 0, 0, 0);
    delay(500);  
    start = 1;
    level--;
  }
  Serial.println(level);

  // Winning the game
  if(level == 5)
  {
    rainbowCycle(100, 10);    
  }

}

void rainbowCycle(int currentSpeed, int stripLen) {
  uint32_t offset = millis() / currentSpeed;
  for(int i=0; i<10; ++i) 
  {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
}

// Interrupts
void leftbutton()
{
  leftFlag = 1; 
}

void rightbutton()
{
  rightFlag = 1; 
}