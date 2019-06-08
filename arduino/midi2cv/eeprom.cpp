#include <Wire.h>
#include "eeprom.h"

Config::Config(byte addr)
{
	Wire.begin();
	this->devaddr = addr;
}

void Config::Load()
{
	byte *s = (byte *)this;
	for (int i = 0; i < sizeof(this->mem); i++)
	{
		*s++ = this->readAddr(i);
	}
}
void Config::Write(int addr, byte val)
{
	this->writeAddr(addr, val);
	this->setmem(addr, val);
}

byte Config::Read(int addr)
{
	byte val = this->readAddr(addr);
	this->setmem(addr, val);
	return val;
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

void Config::setmem(int addr, byte val)
{
	// hacketyhack
	byte *s = (byte *)this;
	s += addr;
	*s = val;
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
	delay(5);
}

byte Config::readAddr(unsigned int addr)
{
	Wire.beginTransmission(this->devaddr);
	Wire.write((int)(addr >> 8));
	Wire.write((int)(addr & 0xFF));
	Wire.endTransmission();
	Wire.requestFrom(this->devaddr, 1);

	byte r = 0xaa;
	if (Wire.available())
		r = Wire.read();
	return r;
}