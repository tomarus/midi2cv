#ifndef ARP_H
#define ARP_H

#include "Arduino.h"

#define NOTE_BUFFER 32
#define MIN_ARP_SPEED 10
#define MAX_ARP_SPEED 300
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