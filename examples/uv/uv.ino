//
// FaBo UV Brick
//
// brick_i2c_uv
//

#include <Wire.h>
#include "fabo-si1132.h"

void setup()
{
  Serial.begin(115200); // シリアルの開始デバック用
   
  Serial.println("Checking I2C device...");
  
  if(faboUV.SearchDevice()){
    Serial.println("I am Si1132");
    faboUV.reset();
    faboUV.configuration();
  }
}

void loop()
{ 
  double uvindex = faboUV.readUV();
  double ir = faboUV.readIR();
  double visible = faboUV.readVisible();
  
  Serial.print("UV Index:");
  Serial.println(uvindex);
  Serial.print("IR Index:");
  Serial.println(ir);
  Serial.print("Visible Index:");
  Serial.println(visible);
  delay(1000);
}
