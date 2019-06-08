#include <SPI.h>
#include <DAC_MCP49xx.h>
#include <MIDI.h>
#include "eeprom.h"

#define PIN_595_SER 4
#define PIN_595_SRCLK 5
#define PIN_595_RCLK 6
#define PIN_DAC2_CS 7
#define PIN_LED 8
#define PIN_GATE2 9
#define PIN_DAC1_CS 10
#define PIN_GATE1 12
#define PIN_POT_SPEED A0

#define TRANSPOSE -36
#define NOTE_BUFFER 128
#define MAX_ARP_SPEED 100

MIDI_CREATE_DEFAULT_INSTANCE();

Config cfg(0x50); // I2C addr of 24LC256

DAC_MCP49xx dac1(DAC_MCP49xx::MCP4922, PIN_DAC1_CS); // DAC model, CS pin, LDAC pin
DAC_MCP49xx dac2(DAC_MCP49xx::MCP4922, PIN_DAC2_CS); // DAC model, CS pin, LDAC pin

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

	dac1.setSPIDivider(SPI_CLOCK_DIV2);
	dac1.setAutomaticallyLatchDual(false);
	dac1.setPortWrite(true);

	dac2.setSPIDivider(SPI_CLOCK_DIV2);
	dac2.setAutomaticallyLatchDual(false);
	dac2.setPortWrite(true);

	MIDI.begin(1);
	MIDI.setHandleClock(handleClock);
	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.setHandleControlChange(handleControl);
	MIDI.setHandleStop(handleStop);
	MIDI.setHandleSystemExclusive(handleSysex);
}

bool onoff;
unsigned long time = millis();
void loop()
{
	if (MIDI.read())
	{
		// toggle led activity light
		onoff = !onoff;
		digitalWrite(PIN_LED, onoff);
	}

	int speed = analogRead(PIN_POT_SPEED);
	int val = map(speed, 0, 1023, 10, MAX_ARP_SPEED);

	unsigned long newtime = time + val;
	if (millis() >= newtime)
	{
		playarploop();
		time = newtime;
	}

	// Test Programmable outputs by sending random gates.
	// digitalWrite(PIN_595_RCLK, 0);
	shiftOut(PIN_595_SER, PIN_595_SRCLK, PIN_595_RCLK, rand());
	// digitalWrite(PIN_595_RCLK, 1);
}

int notes[NOTE_BUFFER];  // pressed notes
int pnotes[NOTE_BUFFER]; // playing notes
int maxnote = 0;
int maxpnote = 0;
int curnote = 0;
bool sustain = false;
long lastNoteOff = millis();

void playarploop()
{
	if (curnote >= maxpnote)
	{
		curnote = 0;
	}
	int val = map(pnotes[curnote] + TRANSPOSE, 0, 59, 0, 4095);
	dac1.output2(val, val);
	dac2.output2(val, val);
	curnote++;
}

void handleNoteOn(byte chan, byte note, byte vel)
{
	if (lastNoteOff < millis() - 20)
	{
		removeAllPlayingNotes();
	}

	notes[maxnote] = note;
	maxnote++;

	pnotes[maxpnote] = note;
	maxpnote++;

	int val = map(note + TRANSPOSE, 0, 59, 0, 4095);
	dac1.output2(val, val);
	dac2.output2(val, val);
	digitalWrite(PIN_GATE1, true);
	digitalWrite(PIN_GATE2, true);

	curnote = maxpnote > 0 ? maxpnote - 1 : 0;
	// time = millis();
}

void removePlayingNote(byte note)
{
	int j = 0;
	for (int i = 0; i < maxpnote; i++)
	{
		if (pnotes[i] != note)
		{
			pnotes[j++] = pnotes[i];
		}
	}
	maxpnote--;
}

void removeAllPlayingNotes()
{
	for (int i = 0; i < maxnote; i++)
	{
		pnotes[i] = notes[i];
	}
	maxpnote = maxnote;
}

void handleNoteOff(byte dhan, byte note, byte vel)
{
	digitalWrite(PIN_GATE1, false);
	digitalWrite(PIN_GATE2, false);

	int j = 0;
	for (int i = 0; i < maxnote; i++)
	{
		if (notes[i] != note)
		{
			notes[j++] = notes[i];
		}
	}
	maxnote--;
}

// handle sustain pedal
void handleControl(byte chanl, byte cc, byte val)
{
	// sustain pedal
	if (cc != 64)
	{
		return;
	}
	sustain = val > 0;

	if (val == 0)
	{
		removeAllPlayingNotes();
	}
}

void handleStop()
{
	maxpnote = 0;
	maxnote = 0;
	curnote = 0;
	sustain = false;
}

static void handleSysex(byte *array, unsigned size)
{
	if (size < 5)
		return;
	if (!(array[1] == 0x7d && array[2] == 0x2a && array[3] == 0x4f))
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
			break;
		}
		}
	}
}

int ticks = 0;
// int counter = 0;
byte clock = 0x00;

void handleClock(void)
{

	ticks++;
	if (ticks == 6)
	{
		ticks = 0;
		// counter++;
		// if (counter == 64)
		// {
		// 	counter = 0;
		// }

		clock++;
		shiftOut(PIN_595_SER, PIN_595_SRCLK, PIN_595_RCLK, clock);

		// if (counter%2==0) {
		// 	digitalWrite(CLOCK2_PIN, HIGH);
		// }
		// if (counter%4==0) {
		// 	digitalWrite(CLOCK4_PIN, HIGH);
		// }
		// if (counter%8==0) {
		// 	digitalWrite(CLOCK8_PIN, HIGH);
		// }
		// if (counter%16==0) {
		// 	digitalWrite(CLOCK16_PIN, HIGH);
		// }
		// if (counter%32==0) {
		// 	digitalWrite(CLOCK32_PIN, HIGH);
		// }
	}
}

// shiftOut sets the 8 programmable gates to the
// individual bits of the data byte input.
void shiftOut(int ser, int srclk, int rclk, byte data)
{
	digitalWrite(rclk, 0);
	// digitalWrite(ser, 0);
	// digitalWrite(srclk, 0);
	for (int i = 7; i >= 0; i--)
	{
		digitalWrite(srclk, 0);
		digitalWrite(ser, data & (1 << 1));
		digitalWrite(srclk, 1);
		// digitalWrite(ser, 0);
	}
	// digitalWrite(srclk, 0);
	digitalWrite(rclk, 1);
}