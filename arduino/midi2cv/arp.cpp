#include "arp.h"

int bound(int val)
{
	if (val < 0)
	{
		return 0;
	}
	else if (val > 4095)
	{
		return 4095;
	}
	else
	{
		return val;
	}
}

Arp::Arp()
{
	this->maxnote = 0;
	this->maxpnote = 0;
	this->curnote = 0;
	this->time = millis();
	this->lastNoteOff = millis();

	this->Pitch = 0;
	this->Transpose = 0;
}

void Arp::Reset()
{
	this->curnote = 0;
}

int Arp::PlayNote()
{
	this->curnote++;
	if (this->curnote >= this->maxpnote)
	{
		this->curnote = 0;
	}
	return scaleNote(this->pnotes[this->curnote]);
}

int Arp::CheckPlayNote(int speed)
{
	int val = map(speed, 0, 1023, MIN_ARP_SPEED, MAX_ARP_SPEED);

	unsigned long newtime = this->time + val;
	if (millis() >= newtime)
	{
		this->time = newtime;
		return this->PlayNote();
	}
	return -1;
}

int Arp::HandleNoteOn(byte note)
{
	int val = -1;

	if (this->lastNoteOff < millis() - 20)
	{
		this->removeAllPlayingNotes();
	}

	if (this->maxnote == 0)
	{
		val = this->scaleNote(note);
		this->curnote = 0;
		this->time = millis();
	}

	this->notes[this->maxnote] = note;
	this->maxnote++;

	this->pnotes[this->maxpnote] = note;
	this->maxpnote++;

	return val;
}

bool Arp::HandleNoteOff(byte note)
{
	int j = 0;
	for (int i = 0; i < this->maxnote; i++)
	{
		if (this->notes[i] != note)
		{
			this->notes[j++] = this->notes[i];
		}
	}
	if (this->maxnote > 0)
		this->maxnote--;
	return this->maxnote == 0;
}

void Arp::removeAllPlayingNotes()
{
	for (int i = 0; i < this->maxnote; i++)
	{
		this->pnotes[i] = this->notes[i];
	}
	this->maxpnote = this->maxnote;
}

int Arp::scaleNote(byte note)
{
	return bound(map(note - this->Transpose + 64, 0, 59, 0, 4095) + this->Pitch);
}
