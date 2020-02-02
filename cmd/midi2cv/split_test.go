package main

import "testing"

func TestSplit(t *testing.T) {
	split := 48
	t1 := -24
	t2 := 36

	note := 84
	if note >= split {
		note = note + t1
		t.Logf("split=%d", note)
	}

	note = 32
	if note < split {
		note = note + t2
		t.Logf("split=%d", note)
	}
}
