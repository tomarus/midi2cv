#ifndef EEPROM_H
#define EEPROM_H

#include "Arduino.h"

struct cfgmem
{
	// 0x00
	byte _mode; // TODO: not implemented yet
	byte split; // split at key N instead of 2 midi channels, set transpose1+2 too
	byte midi1; // midi input channel 1
	byte midi2; // midi input channel 2
	// 0x04
	byte transpose1; // transpose channel 1
	byte transpose2; // transpose channel 2
	byte cc1;		 // cc msg number for channel 1
	byte cc2;		 // cc msg number for channel 2
	// 0x08
	byte cc1ch;	// midi channel for cc msgs chan 1
	byte cc2ch;	// midi channel for cc msgs chan 2
	byte pb1range; // pitchbend output1 range
	byte pb2range; // pitchbend output2 range
	// 0x0c
	byte midi1sync;  // 0 = use pot for speed, 1..N = use N midi clock ticks for speed
	byte midi2sync;  // 1..N = use N midi clock ticks for speed
	byte clockticks; // Advance the clock divider each this many midi clock ticks
	byte _reserved;

	byte pmode[8]; // TODO: not implemented yet
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