// Command midiconfig provides configuration for the MIDI router.
package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"

	"github.com/scgolang/midi"
)

// byteconv converts a string to a byte.
func byteconv(in string) byte {
	base := 10
	if strings.HasPrefix(in, "0x") {
		in = strings.TrimPrefix(in, "0x")
		base = 16
	}
	n, _ := strconv.ParseUint(in, base, 32)
	return byte(n & 0xff)
}

func sysexWrite(device *midi.Device, addr, data byte) {
	var req = []byte{0xf0, 0x7d, 0x2a, 0x4f, 0x01, addr, data, 0xf7}
	n, err := device.Write(req)
	if err != nil {
		log.Fatalf("can't send configuration request: %v", err)
	}
	if n != len(req) {
		log.Fatalf("can't send all configuration data: %d != %d", n, len(req))
	}
}

func main() {
	flag.Usage = func() {
		fmt.Fprintf(flag.CommandLine.Output(), "Usage of %s:\n", os.Args[0])
		fmt.Fprintf(flag.CommandLine.Output(), "\t%s [flags] command [args]\n", os.Args[0])
		fmt.Fprintf(flag.CommandLine.Output(), "\t%s [flags] write 0xADDR 0xBYTE\n", os.Args[0])
		flag.PrintDefaults()
	}
	optL := flag.Bool("l", false, "List devices")
	optD := flag.String("d", "", "Device to use")
	flag.Parse()
	command := flag.Args()
	if (*optD == "" || len(command) == 0) && !*optL {
		flag.Usage()
		os.Exit(0)
	}

	devices, err := midi.Devices()
	if err != nil {
		log.Fatal(err)
	}
	if len(devices) == 0 {
		log.Fatal("No MIDI devices detected")
	}

	if *optL {
		for _, d := range devices {
			fmt.Printf("%s\t%s\n", d.ID, d.Name)
		}
		os.Exit(0)
	}

	//

	var device *midi.Device
	for _, d := range devices {
		if d.ID == *optD || d.Name == *optD {
			device = d
			break
		}
	}
	if device == nil {
		log.Fatalf("can't find midi device: %s", *optD)
	}
	if err := device.Open(); err != nil {
		log.Fatal(err)
	}

	//

	switch command[0] {
	case "write":
		sysexWrite(device, byteconv(command[1]), byteconv(command[2]))
	default:
		fmt.Printf("Supported command: %s\n", command[0])
	}
}
