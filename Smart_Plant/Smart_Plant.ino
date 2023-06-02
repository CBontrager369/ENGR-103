#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int value; 
volatile bool switchFlag = 0;
bool switchVal = 0;
int switchPin = 7;
AsyncDelay delay_6s;

void setup ()
{
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchPin), onoff, CHANGE);
  switchVal = digitalRead(switchPin);
  delay_6s.start(6000, AsyncDelay::MILLIS);
}

void loop()
{
  // "Temperature"
  value = CircuitPlayground.temperatureF();
  Serial.print("Temp (Farenheit): ");
  Serial.println(value);
  delay(100);

    if(value>=90)
  {
    CircuitPlayground.setPixelColor(0, 255, 0, 0);
    CircuitPlayground.setPixelColor(1, 255, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 255);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
  } else if (value > 87)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    CircuitPlayground.setPixelColor(1, 255, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 255);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
  } else if (value > 84)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    CircuitPlayground.setPixelColor(1, 0, 0, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 255);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
  } else if (value > 81)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    CircuitPlayground.setPixelColor(1, 0, 0, 0);
    CircuitPlayground.setPixelColor(2, 0, 0, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 255);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
  } else if (value > 0)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    CircuitPlayground.setPixelColor(1, 0, 0, 0);
    CircuitPlayground.setPixelColor(2, 0, 0, 0);
    CircuitPlayground.setPixelColor(3, 0, 0, 0);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
  }

  if(value > 92 && !switchVal)
  {
    CircuitPlayground.playTone(500, 100);
    delay(100);
  }  

  // "Soil Moisture"
  int val = CircuitPlayground.readCap(6);
  val = map(val, 200, 1023, 0, 255);
  Serial.print("Soil Moisture: ");
  Serial.println(CircuitPlayground.readCap(6));

  CircuitPlayground.setPixelColor(5, 255 - val, val, 0);
  CircuitPlayground.setPixelColor(6, 255 - val, val, 0);

  // "Light"
  int light = CircuitPlayground.lightSensor();
  light = map(light, 0, 1023, 0, 255);
  
  Serial.print("Light Sensor: ");
  Serial.println(light);

  CircuitPlayground.setPixelColor(8, light, light, light);
  CircuitPlayground.setPixelColor(9, light, light, light);  

  if (delay_6s.isExpired()) {
    if(light > 40 && !switchVal)
  {
    //play happy tone
    CircuitPlayground.playTone(70, 400);
    CircuitPlayground.playTone(90, 100);
    CircuitPlayground.playTone(110, 200); 
    Serial.println("Sound on, happy");
  } else if(light < 39 && !switchVal)
  {
    //play sad tone  
    CircuitPlayground.playTone(70, 400);
    CircuitPlayground.playTone(60, 100);
    CircuitPlayground.playTone(50, 200); 
    Serial.println("Sound on, sad");
  }  
    delay_6s.repeat();
  }

  // if(light > 100 && !switchVal)
  // {
  //   //play happy tone
  //   CircuitPlayground.playTone(50, 400);
  //   CircuitPlayground.playTone(60, 100);
  //   CircuitPlayground.playTone(70, 200); 
  //   Serial.println("Sound on");
  // } else if(light < 100 && !switchVal)
  // {
  //   //play sad tone  
  //   CircuitPlayground.playTone(70, 400);
  //   CircuitPlayground.playTone(60, 100);
  //   CircuitPlayground.playTone(50, 200); 
  //   Serial.println("Sound on");
  // }  


  // "Night Switch"
  if (switchFlag)
    {
      delay(5);
      switchVal = digitalRead(switchPin); 
      switchFlag = 0;              
    }
  
  if(switchVal)
  {
    Serial.print("Night Mode: ");    
    Serial.println("on");
  } else if(!switchVal)
  {
    Serial.print("Night Mode: ");    
    Serial.println("off");    
  }
}

void onoff()
{
  switchFlag = 1;        
}