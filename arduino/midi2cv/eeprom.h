#ifndef EEPROM_H
#define EEPROM_H

#include "Arduino.h"

#define CFG_MODE 0
#define CFG_SPLIT 1
#define CFG_MIDI1 2
#define CFG_MIDI2 3
#define CFG_TRANSPOSE1 4
#define CFG_TRANSPOSE2 5
#define CFG_CC1 6
#define CFG_CC2 7

struct cfgmem
{
	byte mode;
	byte split;
	byte midi1;
	byte midi2;
	byte transpose1;
	byte transpose2;
	byte cc1;
	byte cc2;
	byte _[8];
	byte pmode[16];
	byte pnote[16];
	byte pclock[16];
};

class Config
{
public:
	Config(byte addr);
	void Load();

	void Write(int, byte);
	byte Read(int);
	byte Len();

	byte PMode(int);
	byte PNote(int);
	byte PClock(int);

private:
	int devaddr;
	cfgmem mem;

	void readAll();
	void writeAll();
	void writeAddr(unsigned int, byte);
	byte readAddr(unsigned int);
};

#endif