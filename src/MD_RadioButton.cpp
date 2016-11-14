/*
   MD_RadioButton.h - Library for radio button style switch groups.

  See main header file for information.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 */

#include "MD_RadioButton.h"

#define DEBUG 0

#if DEBUG
#define PRINTS(s)   { Serial.print(F(s)); }
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }
#else
#define PRINTS(s)
#define PRINT(s, v)
#endif // DEBUG

#define	UNSELECT_PIN(p)	pinMode(p, _onState == LOW ? INPUT_PULLUP : INPUT)
#define	SELECT_PIN(p)	{ pinMode(p, OUTPUT); digitalWrite(p, HIGH); }

MD_RadioButton::MD_RadioButton(uint8_t pinCount, uint8_t *pinArray, uint8_t onState) :
_pinCount(pinCount), _pinArray(pinArray), _onState(onState), _curSelect(NO_SELECT), _cb(NULL)
{
}

void MD_RadioButton::begin(void)
{
	for (uint8_t p=0; p<_pinCount; p++)
		UNSELECT_PIN(_pinArray[p]);
}

void MD_RadioButton::handleNewSelection(uint8_t x)
{
  UNSELECT_PIN(_pinArray[_curSelect]);
  _curSelect = x;
  SELECT_PIN(_pinArray[_curSelect]);
  if (_cb != NULL) 
    _cb(_curSelect);
}

uint8_t MD_RadioButton::read(void)
// Return the index of the selected button if one is pressed.
// If a callback is defined, call it.
// For the pressed button, convert it to an output and set the 
// LED (same pin numer) on. for the previous selection changes 
// it to work as an input again.
{
	uint8_t sel = NO_SELECT;
	
	for (uint8_t p=0; p<_pinCount; p++)
	{
    // do we have a new selection?
	  if (p != _curSelect && digitalRead(_pinArray[p]) == _onState)
	  {
      handleNewSelection(p);
		  sel = p;
      break;
	  }
	}

	return(sel);
}

void MD_RadioButton::lampTest(void)
// flash all the lamps
{
  uint8_t s = _curSelect;

  for (uint8_t p = 0; p < _pinCount; p++)
  {
    select(p);
    delay(300);
  }

  select(s);
}
