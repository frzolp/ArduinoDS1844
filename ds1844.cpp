/*
  ds1844.cpp - A library for controlling the Dallas Semiconductor DS1844
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
#include "ds1844.h"

// DS1844 object
DS1844::DS1844(int dataPin, int clkPin, int rwPin, int rstPin)
{
	// set the pin assignments
	SPI_DIN = dataPin;
	SPI_CLK = clkPin;
	SPI_RW = rwPin;
	SPI_RST = rstPin;

	// define pins as outputs
	pinMode(SPI_DIN, OUTPUT);
	pinMode(SPI_CLK, OUTPUT);
	pinMode(SPI_RW, OUTPUT);
	pinMode(SPI_RST, OUTPUT);
	// set RW to HIGH so we don't
	// grab data all willy-nilly
	digitalWrite(SPI_RW, HIGH);
	// set RST to LOW to temporarily
	// disable the serial interface
	// until it's magic time.
	digitalWrite(SPI_RST, LOW);
}

void DS1844::spiTransfer(int pot, int val)
{
	/* 1 byte = 8 bits. Conveniently enough,
	 * that's also the length of data the DS1844
	 * needs to address and assign the quad pots */
	byte data;
	// take the 2-bit pot address (0 - 3)
	// and shift it to the 2 most significant bits
	data = pot << 6;
	// append the six-bit position setting to the byte
	data = data + val;

	// set RW to LOW; this puts DS1866 into write mode
	digitalWrite(SPI_RW, LOW);
	// set RST to HIGH; data can now be transmitted
	digitalWrite(SPI_RST, HIGH);
	// shift the data into the DS1866, starting with
	// the most significant bit, clocking like mad
	shiftOut(SPI_DIN, SPI_CLK, MSBFIRST, data);
	// set RST to LOW because loose lips sink ships
	digitalWrite(SPI_RST, LOW);
	// set RW to HIGH to flat-out refuse to listen
	digitalWrite(SPI_RW, HIGH);
}

void DS1844::clear(int pot)
{
	// simply sets the specified potentiometer to low
	spiTransfer(pot, 0);
}

void DS1844::setAll(int val)
{
	// set all four potentiometers to the specified value
	for (int i = 0; i <= 3; i++)
	{
		spiTransfer(i, val);
	}
}

void DS1844::setVal(int pot, int val)
{
	// set one potentiometer to the specified value
	spiTransfer(pot, val);
}
