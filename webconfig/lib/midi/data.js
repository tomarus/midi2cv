const Status = [
	'Note Off',
	'Note On',
	'Poly Press',
	'Controller',
	'Program Change',
	'Channel Pressure',
	'Pitch Bend'
]

const System = [
	'System Exclusive',
	'Time Code',
	'Song Position',
	'Song Select',
	'Unknown System 04',
	'Unknown System 05',
	'Tune Request',
	'EOX',
	'Clock Tick',
	'Unknown System 09',
	'Start',
	'Continue',
	'Stop',
	'Unknown System 0d',
	'Active Sensing',
	'System Reset'
]
// offset is note 35 (0x23)
const GMPercussion = [
	'Bass Drum 2',
	'Bass Drum 1',
	'Side Stick/Rimshot',
	'Snare Drum 1',
	'Hand Clap',
	'Snare Drum 2',
	'Low Tom 2',
	'Closed Hi-hat',
	'Low Tom 1',
	'Pedal Hi-hat',
	'Mid Tom 2',
	'Open Hi-hat',
	'Mid Tom 1',
	'High Tom 2',
	'Crash Cymbal 1',
	'High Tom 1',
	'Ride Cymbal 1',
	'Chinese Cymbal',
	'Ride Bell',
	'Tambourine',
	'Splash Cymbal',
	'Cowbell',
	'Crash Cymbal 2',
	'Vibra Slap',
	'Ride Cymbal 2',
	'High Bongo',
	'Low Bongo',
	'Mute High Conga',
	'Open High Conga',
	'Low Conga',
	'High Timbale',
	'Low Timbale',
	'High Agogô',
	'Low Agogô',
	'Cabasa',
	'Maracas',
	'Short Whistle',
	'Long Whistle',
	'Short Güiro',
	'Long Güiro',
	'Claves',
	'High Wood Block',
	'Low Wood Block',
	'Mute Cuíca',
	'Open Cuíca',
	'Mute Triangle',
	'Open Triangle'
]

let Controllers = [
	'Bank Select',		// 0x00
	'Mod Wheel',
	'Breath',
	'Unknown CC 03',
	'Foot Ctrlr',
	'Portamento',
	'Data MSB',
	'Volume',
	'Balance',			// 0x08
	'Unknown CC 09',
	'Pan',
	'Expression',
	'Effect 1',
	'Effect 2',
	'Unknown CC 0e',
	'Unknown CC 0f',
	'General 1',		// 0x10
	'General 2',
	'General 3',
	'General 4',
	'Unknown CC 14',
	'Unknown CC 15',
	'Unknown CC 16',
	'Unknown CC 17',
	'Unknown CC 18',	// 0x18
	'Unknown CC 19',
	'Unknown CC 1a',
	'Unknown CC 1b',
	'Unknown CC 1c',
	'Unknown CC 1d',
	'Unknown CC 1e',
	'Unknown CC 1f',
	'Ctrlr 00 LSB',		// 0x20
	'Ctrlr 01 LSB',
	'Ctrlr 02 LSB',
	'Ctrlr 03 LSB',
	'Ctrlr 04 LSB',
	'Ctrlr 05 LSB',
	'Ctrlr 06 LSB',
	'Ctrlr 07 LSB',
	'Ctrlr 08 LSB',
	'Ctrlr 09 LSB',
	'Ctrlr 0a LSB',
	'Ctrlr 0b LSB',
	'Ctrlr 0c LSB',
	'Ctrlr 0d LSB',
	'Ctrlr 0e LSB',
	'Ctrlr 0f LSB',
	'Ctrlr 10 LSB',		// 0x30
	'Ctrlr 11 LSB',
	'Ctrlr 12 LSB',
	'Ctrlr 13 LSB',
	'Ctrlr 14 LSB',
	'Ctrlr 15 LSB',
	'Ctrlr 16 LSB',
	'Ctrlr 17 LSB',
	'Ctrlr 18 LSB',
	'Ctrlr 19 LSB',
	'Ctrlr 1a LSB',
	'Ctrlr 1b LSB',
	'Ctrlr 1c LSB',
	'Ctrlr 1d LSB',
	'Ctrlr 1e LSB',
	'Ctrlr 1f LSB',
	'Sustain',			// 0x40
	'Portamento',
	'Sustenuto',
	'Soft',
	'Legato',
	'Hold 2',
	'Sound Ctrl 1',
	'Sound Ctrl 2',
	'Sound Ctrl 3',		// 0x48
	'Sound Ctrl 4',
	'Sound Ctrl 5',
	'Sound Ctrl 6',
	'Sound Ctrl 7',
	'Sound Ctrl 8',
	'Sound Ctrl 9',
	'Sound Ctrl 10',
	'Switch 1',			// 0x50
	'Switch 2',
	'Switch 3',
	'Switch 4',
	'Portamento CC',
	'Unknown CC 55',
	'Unknown CC 56',
	'Unknown CC 57',
	'Unknown CC 58',	// 0x58
	'Unknown CC 59',
	'Unknown CC 5a',
	'Effect 1 Depth',
	'Effect 2 Depth',
	'Effect 3 Depth',
	'Effect 4 Depth',
	'Effect 5 Depth',
	'Data Increment', 	// 0x60
	'Data Decrement',
	'Custom LSB',
	'Custom MSB',
	'Registered LSB',
	'Registered MSB',
	'Unknown CC 66',
	'Unknown CC 67',
	'Unknown CC 68',	// 0x68
	'Unknown CC 69',
	'Unknown CC 6a',
	'Unknown CC 6b',
	'Unknown CC 6c',
	'Unknown CC 6d',
	'Unknown CC 6e',
	'Unknown CC 6f',
	'Unknown CC 70',	// 0x70
	'Unknown CC 71',
	'Unknown CC 72',
	'Unknown CC 73',
	'Unknown CC 74',
	'Unknown CC 75',
	'Unknown CC 76',
	'Unknown CC 77',
	'Unknown CC 78',	// 0x78
	'Reset All CC',
	'Local Control',
	'All Notes Off',
	'Omni Mode Off',
	'Omni Mode On',
	'Mono Mode',
	'Poly Mode'
]

const data = {Controllers, GMPercussion, Status, System}
export default data
