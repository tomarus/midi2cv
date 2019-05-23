#include <SPI.h>
#include <DAC_MCP49xx.h>
#include <MIDI.h>
#include "eeprom.h"

#define LED_PIN 2
#define PIN_GATE 4

#define POT_SPEED A0

#define TRANSPOSE -36
#define NOTE_BUFFER 128

MIDI_CREATE_DEFAULT_INSTANCE();
DAC_MCP49xx dac(DAC_MCP49xx::MCP4922, 10); // DAC model, CS pin, LDAC pin
Config cfg(0x50);						   // i2c addr of 24LC256

long lastNoteOff = millis();

void setup()
{
	pinMode(LED_PIN, OUTPUT);
	pinMode(PIN_GATE, OUTPUT);
	digitalWrite(LED_PIN, true);
	digitalWrite(PIN_GATE, false);

	cfg.Load();

	dac.setSPIDivider(SPI_CLOCK_DIV2);
	dac.setAutomaticallyLatchDual(false);
	dac.setPortWrite(true);

	MIDI.begin(1);
	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.setHandleControlChange(handleControl);
	MIDI.setHandleClock(handleClock);
	MIDI.setHandleClock(handleStop);
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
		digitalWrite(LED_PIN, onoff);
	}

	int speed = analogRead(POT_SPEED);
	int val = map(speed, 0, 1023, 10, 100);

	unsigned long newtime = time + val;
	if (millis() >= newtime)
	{
		playarploop();
		time = newtime;
	}
}

int notes[NOTE_BUFFER];  // pressed notes
int pnotes[NOTE_BUFFER]; // playing notes
int maxnote = 0;
int maxpnote = 0;
int curnote = 0;
bool sustain = false;

void playarploop()
{
	if (curnote >= maxpnote)
	{
		curnote = 0;
	}
	int val = map(pnotes[curnote] + TRANSPOSE, 0, 59, 0, 4095);
	dac.output2(val, val);
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
	dac.output2(val, val);
	digitalWrite(PIN_GATE, true);

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
	digitalWrite(PIN_GATE, false);

	int j = 0;
	for (int i = 0; i < maxnote; i++)
	{
		if (notes[i] != note)
		{
			notes[j++] = notes[i];
		}
	}
	maxnote--;

	// if (!sustain)
	// {
	// removePlayingNote(note);
	// }

	// if (lastNoteOff < millis() - 20)
	// {
	// 	removePlayingNote(note);
	// 	lastNoteOff = millis();
	// }
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

//bool toggle = false;
void handleClock()
{
	//  toggle = !toggle;
	//  digitalWrite(PIN_4040_CP, toggle);
}

void handleStop()
{
	//  TODO: Enable this when not using midi devbox...
	//  maxpnote = 0;
	//  maxnote = 0;
	//  curnote = 0;
	//  sustain = false;
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
		case 0: // cmd 0x00 = info request
		{
			byte response[] = {0xf0, 0x7d, 0x2a, 0x4d,
							   0x40, 0x01, // RESPONSE 0x40, version 1
							   0x01, 0x00, // 1 inport, 0 outports
							   0xf7};
			MIDI.sendSysEx(sizeof(response), response, true);
			break;
		}
		case 1: // cmd 0x01 = write a config byte
		{
			cfg.Write(array[i + 1], array[i + 2]);
			byte response[] = {0xf0, 0x7d, 0x2a, 0x4d, 0x00, 0xf7}; // 0x00 == OK
			MIDI.sendSysEx(sizeof(response), response, true);
			break;
		}
		case 2: // cmd 0x02 = read config
		{
			byte response[] = {0xf0, 0x7d, 0x2a, 0x4d, cfg.Len()};
			MIDI.sendSysEx(sizeof(response), response, true);
			byte vals[cfg.Len()+1];
			for (int i = 0; i < cfg.Len(); i++)
			{
				vals[i] = cfg.Read(i);
			}
			vals[cfg.Len()] = 0xf7;
			MIDI.sendSysEx(cfg.Len()+1, vals, true);
		}
		}
	}
}
