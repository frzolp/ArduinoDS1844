/*
  ds1844.h - A library for controlling the Dallas Semiconductor DS1844
  Copyright (c) 2012 Francis Zolp

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef ds1844_h
#define ds1844_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class DS1844 {
	private:
		/* Look, I'll be honest with you. Since this is my first
		 * library, and really the first time actually doing
		 * serial transfers (successfully), I used a lot of the conventions 
		 * that were used in Eberhard Fahle's excellent LedControl library. 
		 * And I'm still working on this.
		 */
		// private method to write the data to the DS1844
		void spiTransfer(int pot, int val);
		// definitions for the RW, RST, DIN, and CLK pins
		// used in transmitting data
		int SPI_RW;
		int SPI_RST;
		int SPI_DIN;
		int SPI_CLK;

	public:
		// DS1844 object, used in the Arduino sketch
		DS1844(int dataPin, int clkPin, int rwPin, int rstPin);
		// takes the specified potentiometer (0 - 3) and
		// sets it to the lowest value
		void clear(int pot);
		// sets a specified potentiometer to a specific value (0 - 63)
		void setVal(int pot, int val);
		// sets all four potentiometers to a specific value
		void setAll(int val);
};
#endif
