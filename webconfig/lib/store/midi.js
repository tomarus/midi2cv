import {RefreshMidi} from 'lib/midi/midi'

const REFRESH      = 'midi/REFRESH'
const STATUS       = 'midi/STATUS'
const ERROR        = 'midi/ERROR'
const SET_MIDI     = 'midi/SET_DEVICES'
const SET_PORTS    = 'midi/SET_PORTS'

let initialState = {
	status: 0,
	error: '',
	midi: null,
	inbpm: 0, // received/calculated bpm
	inputs: [],
	outputs: [],
}

export const refreshMidiAction = () => ({
	type: REFRESH
})

export const setStatusAction = (status) => ({
	type: STATUS, status
})

export const setErrorAction = (error) => ({
	type: ERROR, error
})

export const setMidiAction = (midi) => ({
	type: SET_MIDI, midi
})

// export const sysOutAction = (index, sysOut) => ({
// 	type: SYSOUT, index, sysOut
// })

export const setPortsAction = (inputs, outputs) => ({
	type: SET_PORTS, inputs, outputs
})

export default function reducer (state = initialState, action = {}) {
	let newState = Object.assign({}, state)

	switch (action.type) {

	case REFRESH:
		RefreshMidi()
		return state

	case STATUS:
		newState.status = action.status
		return newState

	case ERROR:
		newState.error = action.error
		console.error('MIDI Error Received', action.error)
		return newState

	case SET_MIDI:
		newState.midi = action.midi
		return newState

	case SET_PORTS:
		newState.inputs = action.inputs
		newState.outputs = action.outputs
		return newState

	default:
		return state
	}
}
