#include <SPI.h>
#include <DAC_MCP49xx.h>
#include <MIDI.h>

#include "eeprom.h"
#include "arp.h"

#define PIN_595_SER 4
#define PIN_595_SRCLK 5
#define PIN_595_RCLK 6
#define PIN_DAC2_CS 7
#define PIN_LED 8
#define PIN_GATE2 9
#define PIN_DAC1_CS 10
#define PIN_GATE1 12
#define PIN_POT_SPEED A0

// Only change this if you have more than one Miarph
#define MIARPH_DEVICE_ID 0x4f

MIDI_CREATE_DEFAULT_INSTANCE();

Config cfg(0x50); // I2C addr of 24LC256

DAC_MCP49xx dac1(DAC_MCP49xx::MCP4922, PIN_DAC1_CS); // DAC model, CS pin, LDAC pin
DAC_MCP49xx dac2(DAC_MCP49xx::MCP4922, PIN_DAC2_CS); // DAC model, CS pin, LDAC pin

Arp arp1;
Arp arp2;

void setup()
{
	pinMode(PIN_595_SER, OUTPUT);
	pinMode(PIN_595_SRCLK, OUTPUT);
	pinMode(PIN_595_RCLK, OUTPUT);

	pinMode(PIN_DAC1_CS, OUTPUT);
	pinMode(PIN_DAC2_CS, OUTPUT);

	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_GATE1, OUTPUT);
	pinMode(PIN_GATE2, OUTPUT);

	digitalWrite(PIN_LED, true);
	digitalWrite(PIN_GATE1, false);
	digitalWrite(PIN_GATE2, false);

	cfg.Load();
	arp1.Transpose = cfg.mem.transpose1;
	arp2.Transpose = cfg.mem.transpose2;
	arp1.Pitch = 0;
	arp2.Pitch = 0;

	dac1.setSPIDivider(SPI_CLOCK_DIV2);
	dac1.setAutomaticallyLatchDual(false);
	dac1.setPortWrite(true);

	dac2.setSPIDivider(SPI_CLOCK_DIV2);
	dac2.setAutomaticallyLatchDual(false);
	dac2.setPortWrite(false); // false cos non standard spi port

	dac1.output2(0, 0);
	dac2.output2(0, 0);

	MIDI.begin(0); // channel
	MIDI.setHandleClock(handleClock);
	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.setHandleControlChange(handleControl);
	MIDI.setHandleStop(handleStop);
	MIDI.setHandleStart(handleStart);
	MIDI.setHandleSystemExclusive(handleSysex);
	MIDI.setHandlePitchBend(handlePitchBend);
}

bool onoff;
void toggleled()
{
	onoff = !onoff;
	digitalWrite(PIN_LED, onoff);
}

void loop()
{
	MIDI.read();

	int speed = analogRead(PIN_POT_SPEED);
	if (cfg.mem.midi1sync == 0)
	{
		int val = arp1.CheckPlayNote(speed);
		if (val != -1)
			dac1.outputA(val);
	}
	if (cfg.mem.midi2sync == 0)
	{
		int val = arp2.CheckPlayNote(speed);
		if (val != -1)
			dac1.outputB(val);
	}
}

byte shiftreg = 0;

void handleNoteOn(byte chan, byte note, byte vel)
{
	if (chan == cfg.mem.midi1 && cfg.mem.split > 0)
	{
		if (note >= cfg.mem.split)
		{
			int val = arp1.HandleNoteOn(note);
			if (val != -1)
			{
				digitalWrite(PIN_GATE1, true);
				dac1.outputA(val);
			}
		}
		if (note < cfg.mem.split)
		{
			int val = arp2.HandleNoteOn(note);
			if (val != -1)
			{
				digitalWrite(PIN_GATE2, true);
				dac1.outputB(val);
			}
		}
		return;
	}

	if (chan == cfg.mem.midi1)
	{
		int val = arp1.HandleNoteOn(note);
		if (val != -1)
		{
			digitalWrite(PIN_GATE1, true);
			dac1.outputA(val);
			return;
		}
	}

	if (chan == cfg.mem.midi2)
	{
		int val = arp2.HandleNoteOn(note);
		if (val != -1)
		{
			digitalWrite(PIN_GATE2, true);
			dac1.outputB(val);
		}
	}

	bool triggered = false;
	for (int i = 0; i < 8; i++)
	{
		if (cfg.mem.pmode[i] == 1 && note == cfg.mem.pnote[i]) {
			shiftreg = shiftreg ^ 1 << i;
			triggered = true;
		}
	}
	if (triggered) {
		shiftOut(PIN_595_SER, PIN_595_SRCLK, PIN_595_RCLK, shiftreg);
	}
}

void handleNoteOff(byte chan, byte note, byte vel)
{
	if (chan == cfg.mem.midi1 && cfg.mem.split > 0)
	{
		if (note >= cfg.mem.split)
		{
			bool gate = arp1.HandleNoteOff(note);
			if (gate)
				digitalWrite(PIN_GATE1, false);
		}
		if (note < cfg.mem.split)
		{
			bool gate = arp2.HandleNoteOff(note);
			if (gate)
				digitalWrite(PIN_GATE2, false);
		}
		return;
	}

	if (chan == cfg.mem.midi1)
	{
		bool gate = arp1.HandleNoteOff(note);
		if (gate)
		{
			digitalWrite(PIN_GATE1, false);
			return;
		}
	}

	if (chan == cfg.mem.midi2)
	{
		bool gate = arp2.HandleNoteOff(note);
		if (gate)
		{
			digitalWrite(PIN_GATE2, false);
		}
	}

	bool triggered = false;
	for (int i = 0; i < 8; i++)
	{
		if (cfg.mem.pmode[i] == 1 && note == cfg.mem.pnote[i]) {
			shiftreg = shiftreg & ~(1 << i);
			triggered = true;
		}
	}
	if (triggered) {
		shiftOut(PIN_595_SER, PIN_595_SRCLK, PIN_595_RCLK, shiftreg);
	}
}

// handle sustain pedal
void handleControl(byte chan, byte cc, byte val)
{
	if (cc == cfg.mem.cc1 && chan == cfg.mem.cc1ch)
	{
		dac2.outputA(val * 32);
		return;
	}

	if (cc == cfg.mem.cc2 && chan == cfg.mem.cc2ch)
	{
		dac2.outputB(val * 32);
		return;
	}
}

void handleStop()
{
	// maxpnote = 0;
	// maxnote = 0;
	// curnote = 0;
}

static void handleSysex(byte *array, unsigned size)
{
	if (size < 5)
		return;
	if (!(array[1] == 0x7d && array[2] == 0x2a && array[3] == MIARPH_DEVICE_ID))
		return;

	for (int i = 4; i < size - 1; i++)
	{
		int command = array[i];
		if (command >= 0x40)
		{
			return;
		}

		switch (command)
		{
		case 1: // cmd 0x01 = write a config byte
		{
			cfg.Write(array[i + 1], array[i + 2]); // addr = byte1, val = byte2
			if (array[i + 1] == 0x04)
			{
				arp1.Transpose = array[i + 2];
			}
			if (array[i + 1] == 0x05)
			{
				arp2.Transpose = array[i + 2];
			}
			break;
		}
		}
	}
}

int ticks = 0;
int midi1ticks = 0;
int midi2ticks = 0;
byte clock = 0xff;
byte oldclock = 0xff;

void handleStart()
{
	ticks = cfg.mem.clockticks - 1;
	midi1ticks = cfg.mem.midi1sync;
	midi2ticks = cfg.mem.midi2sync;
	clock = 0xff;
	oldclock = 0xff;
	arp1.Reset();
	arp2.Reset();
}

void handleClock(void)
{
	midi1ticks++;
	if (cfg.mem.midi1sync > 0 && midi1ticks >= cfg.mem.midi1sync)
	{
		midi1ticks = 0;
		int val = arp1.PlayNote();
		if (val != -1)
		{
			dac1.outputA(val);
		}
	}

	midi2ticks++;
	if (cfg.mem.midi2sync > 0 && midi2ticks >= cfg.mem.midi2sync)
	{
		midi2ticks = 0;
		int val = arp2.PlayNote();
		if (val != -1)
		{
			dac1.outputB(val);
		}
	}

	ticks++;
	if (ticks >= cfg.mem.clockticks)
	{
		toggleled();
		ticks = 0;
		clock++;
		byte val = oldclock ^ clock;
		oldclock = clock;
		for (int i = 0; i < 8; i++) {
			if (cfg.mem.pmode[i] == 0) {
				if (val & 1 << (cfg.mem.pclock[i]+1)) {
					shiftreg = shiftreg ^ 1 << i;
				} else {
					shiftreg = shiftreg & ~(1 << i);
				}
			}
		}
	}
	shiftOut(PIN_595_SER, PIN_595_SRCLK, PIN_595_RCLK, shiftreg);
}

// shiftOut sets the 8 programmable gates to the
// individual bits of the data byte input.
void shiftOut(int ser, int srclk, int rclk, byte data)
{
	digitalWrite(rclk, 0);
	for (int i = 7; i >= 0; i--)
	{
		digitalWrite(srclk, 0);
		digitalWrite(ser, data & (1 << i));
		digitalWrite(srclk, 1);
	}
	digitalWrite(rclk, 1);
}

void handlePitchBend(byte chan, int val)
{
	if (cfg.mem.split > 0)
	{
		arp1.Pitch = (val / (16384 / (4096 / 60)) * cfg.mem.pb1range);
		arp2.Pitch = (val / (16384 / (4096 / 60)) * cfg.mem.pb2range);
		return;
	}

	if (chan == cfg.mem.midi1)
	{
		arp1.Pitch = (val / (16384 / (4096 / 60)) * cfg.mem.pb1range);
	}

	if (chan == cfg.mem.midi2)
	{
		arp2.Pitch = (val / (16384 / (4096 / 60)) * cfg.mem.pb2range);
	}
}