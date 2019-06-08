package main

import (
	"testing"
)

func TestConv(t *testing.T) {
	var tests = []struct {
		in  string
		out byte
	}{
		{"0x04", 4},
		{"32", 32},
	}
	for _, ts := range tests {
		out := byteconv(ts.in)
		if out != ts.out {
			t.Fatalf("in != out %d (%v != %v)", out, ts.in, ts.out)
		}
	}
}
