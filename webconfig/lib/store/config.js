const SET_ADDRESS = 'config/SET_ADDRESS'
const SET_DEVICE = 'config/SET_DEVICE'
const SET_DEVICE_ID = 'config/SET_DEVICE_ID'

const SET_PORT_CLOCK = 'config/SET_PORT_CLOCK'
const SET_PORT_MODE = 'config/SET_PORT_MODE'
const SET_PORT_TRIGGER = 'config/SET_PORT_TRIGGER'

const initialState = {
	device: 0,
	deviceid: 0x4f,
	split: -1,
	channel1: 0,
	channel2: 0,
	transpose1: 0,
	transpose2: 0,
	cc1: -1,
	cc2: -1,
	ccchannel1: 0,
	ccchannel2: 0,
	pitchbend1: -1,
	pitchbend2: -1,
	midi1sync: -1,
	midi2sync: -1,
	clockticks: -1,
	portmodes: [ -1, -1, -1, -1, -1, -1, -1, -1 ],
	porttriggers: [ -1, -1, -1, -1, -1, -1, -1, -1 ],
	portclocks: [ -1, -1, -1, -1, -1, -1, -1, -1 ],
}

export const setConfigAction = (address, value) => ({
	type: SET_ADDRESS, address, value
})

export const setOutputDeviceAction = (device) => ({
	type: SET_DEVICE, device 
})

export const setDeviceIdAction = (id) => ({
	type: SET_DEVICE_ID, id
})

export const setPortModeAction = (index, value) => ({
	type: SET_PORT_MODE, index, value
})

export const setPortClockAction = (index, value) => ({
	type: SET_PORT_CLOCK, index, value
})

export const setPortTriggerAction = (index, value) => ({
	type: SET_PORT_TRIGGER, index, value
})

//

const reducer = (state = initialState, action = {}) => {
	let newState = Object.assign({}, state)

	switch (action.type) {
		case SET_DEVICE:
			newState.device = action.value
			break
		case SET_DEVICE_ID:
			newState.deviceid = action.id
			break
		case SET_PORT_CLOCK:
			newState.portclocks = state.portclocks.map((item, j) => {
				return action.index === j ? action.value : item
			})
			break
		case SET_PORT_MODE:
			newState.portmodes = state.portmodes.map((item, j) => {
				return action.index === j ? action.value : item
			})
			break
		case SET_PORT_TRIGGER:
			newState.porttriggers = state.porttriggers.map((item, j) => {
				return action.index === j ? action.value : item
			})
			break
		case SET_ADDRESS:
			switch (action.address) {
				case 0x01:
					newState.split = action.value
					break
				case 0x02:
					newState.channel1 = action.value
					break
				case 0x03:
					newState.channel2 = action.value
					break
				case 0x04:
					newState.transpose1 = action.value
					break
				case 0x05:
					newState.transpose2 = action.value
					break
				case 0x06:
					newState.cc1 = action.value
					break
				case 0x07:
					newState.cc2 = action.value
					break
				case 0x08:
					newState.ccchannel1 = action.value
					break
				case 0x09:
					newState.ccchannel2 = action.value
					break
				case 0x0a:
					newState.pitchbend1 = action.value
					break
				case 0x0b:
					newState.pitchbend2 = action.value
					break
				case 0x0c:
					newState.midi1sync = action.value
					break
				case 0x0d:
					newState.midi2sync = action.value
					break
				case 0x0e:
					newState.clockticks = action.value
					break
			}
	}
	return newState
}

export default reducer
