#ifndef EEPROM_H
#define EEPROM_H

#include "Arduino.h"

struct cfgmem
{
	byte _mode;
	byte _split;
	byte midi1;
	byte _midi2;
	byte _transpose1;
	byte _transpose2;
	byte cc1;
	byte cc2;
	// 0x08
	byte cc1ch;
	byte cc2ch;
	byte pb1range;
	byte pb2range;
	// 0x0c
	byte midi1sync;
	byte midi2sync;
	byte clockticks;
	byte _reserved;

	byte pmode[8];
	byte pnote[8];
	byte pclock[8];
};

class Config
{
public:
	cfgmem mem;

	Config(byte addr);
	void Load();

	void Write(int, byte);
	byte Len();

	byte PMode(int);
	byte PNote(int);
	byte PClock(int);

private:
	int devaddr;

	void setmem(int, byte);
	void writeAll();
	void writeAddr(unsigned int, byte);
	byte readAddr(unsigned int);
};

#endif