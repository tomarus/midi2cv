#ifndef ARP_H
#define ARP_H

#include "Arduino.h"

#define NOTE_BUFFER 32	// max nr of notes to be arpeggiating
#define MIN_ARP_SPEED 10  // min duration in ms
#define MAX_ARP_SPEED 300 // max duration in ms

class Arp
{
public:
	Arp();
	void Reset();
	int PlayNote();
	int CheckPlayNote(int speed);
	int HandleNoteOn(byte note);
	bool HandleNoteOff(byte note);

	int Transpose;
	int Pitch;

private:
	void removeAllPlayingNotes();
	int scaleNote(byte note);

	long time;
	long lastNoteOff;
	int curnote;
	int maxnote;
	int maxpnote;
	byte notes[NOTE_BUFFER];
	byte pnotes[NOTE_BUFFER];
};

#endif