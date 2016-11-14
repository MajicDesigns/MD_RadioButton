// Example showing use of the MD_RadioButton library
//
#include <MD_RadioButton.h>

#define USE_CALLBACK  0

uint8_t pinArray[] = { 4, 5, 6, 7 };

MD_RadioButton  RB(ARRAY_SIZE(pinArray), pinArray);

void cbNotify(uint8_t sel)
// Callback funtion (when enabled)
{
  Serial.println(sel);
}

void setup() 
{
  Serial.begin(57600);
  Serial.println("[MD_RadioButton]");
  
  RB.begin();
  RB.lampTest();

#if USE_CALLBACK
  Serial.println("Callback enabled");
  RB.setCallback(cbNotify);
#endif // USE_CALLBACK

  RB.select(0);
}

void loop() 
{
#if USE_CALLBACK
  RB.read();
#else
  uint8_t sel;

  if ((sel = RB.read()) != NO_SELECT)
    Serial.println(sel);
#endif
}
