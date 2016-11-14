/*
  MD_RadioButton.h - Library for radio button style switch groups.
  
  Small library to allow the use of momentary push switches with LEDs to operate as user
  radio button style selction buttons.
  
  v1.0 March 2016
  - New library
	
  Copyright Marco Colli 2016.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

#include <Arduino.h>

// Default values.
#define KEY_ON_STATE	LOW // default active low - transition high to low
#define	NO_SELECT		  255	// no selection identifier
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

class MD_RadioButton
{
public:
	MD_RadioButton(uint8_t pinCount, uint8_t *pinArray, uint8_t _onState = KEY_ON_STATE);

	~MD_RadioButton() { };
	
	void begin(void);
	uint8_t read(void);
  void lampTest();
  inline void setCallback(void(*cb)(uint8_t sel)) { _cb = cb; };
  inline void select(uint8_t x) { handleNewSelection(x); };
	
protected:
	uint8_t	_pinCount;    // the number of pins
	uint8_t	*_pinArray;   // the array of pin number (at least pinCount elements)
	uint8_t	_curSelect;		// currently selected pinArray index
	uint8_t	_onState;		  // what is the pressed state for the switch
	void  (*_cb)(uint8_t sel);	// the callback function, NULL --> undefined

  void handleNewSelection(uint8_t x); // programmatically select an option
};
