// TCS230 sensor reading example
//
// This is just to show basic functionality without calibration.
// Utilises the non-blocking version of the reading function.
// Output uses the Serial console.
//
#include <MD_TCS230.h>
#include <FreqCount.h>

// Pin definitions
#define  S2_OUT  12
#define  S3_OUT  13
#define  OE_OUT   8    // LOW = ENABLED 

MD_TCS230  CS(S2_OUT, S3_OUT, OE_OUT);

void setup() 
{
  Serial.begin(57600);
  Serial.println("[TCS230 Simple NON_BLOCKING Example]");
  Serial.println("\nMove the sensor to different color to see the RGB value");
  Serial.println("Note: These values are being read in without sensor calibration");
  Serial.println("and are likely to be far from reality");

  CS.begin();
}

void readSensor()
{
  static  bool  waiting;
  
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available()) 
    {
      // Dump the current raw sensor reading
      Serial.print("Raw [");
      Serial.print(CS._Fo.value[0]);
      Serial.print(",");
      Serial.print(CS._Fo.value[1]);
      Serial.print(",");
      Serial.print(CS._Fo.value[2]);
      Serial.println("]");
      
      colorData  rgb;
      
      // Dump the color data recovered from the raw data.
      // These data are most likely not useful as there was no
      // calibration taking place.
      CS.getRGB(&rgb);
      Serial.print("RGB [");
      Serial.print(rgb.value[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
      
      waiting = false;
    }
  }
}


void loop() 
{
  readSensor();
}

