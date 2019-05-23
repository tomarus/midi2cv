#include <Wire.h>
#include "eeprom.h"

Config::Config(byte addr)
{
	this->devaddr = addr;
}

void Config::Load()
{
	this->readAll();
}

void Config::Write(int n, byte val)
{
	this->writeAddr(n, val);
}

byte Config::Read(int n)
{
	return this->readAddr(n);
}

byte Config::Len()
{
	return sizeof(this->mem);
}

//

byte Config::PMode(int n)
{
	return this->mem.pmode[n];
}

byte Config::PNote(int n)
{
	return this->mem.pnote[n];
}

byte Config::PClock(int n)
{
	return this->mem.pclock[n];
}

//

void Config::readAll()
{
	byte *s = (byte *)this;
	for (int i = 0; i < sizeof(this->mem); i++)
	{
		*s++ = this->readAddr(i);
	}
}

void Config::writeAll()
{
	const byte *s = (const byte *)this;
	for (int i = 0; i < sizeof(this->mem); i++)
	{
		this->writeAddr(i, *s++);
	}
}

void Config::writeAddr(unsigned int addr, byte data)
{
	Wire.beginTransmission(this->devaddr);
	Wire.write((int)(addr >> 8));
	Wire.write((int)(addr & 0xFF));
	Wire.write(data);
	Wire.endTransmission();
}

byte Config::readAddr(unsigned int addr)
{
	Wire.beginTransmission(this->devaddr);
	Wire.write((int)(addr >> 8));
	Wire.write((int)(addr & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(this->devaddr, 1);

	byte r;
	if (Wire.available())
		r = Wire.read();
	return r;
}