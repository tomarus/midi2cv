const SET_ADDRESS = 'config/SET_ADDRESS'
const SET_DEVICE = 'config/SET_DEVICE'

const initialState = {
	device: 0,
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
}

export const setConfigAction = (address, value) => ({
	type: SET_ADDRESS, address, value
})

export const setOutputDeviceAction = (device) => ({
	type: SET_DEVICE, device 
})

//

const reducer = (state = initialState, action = {}) => {
	let newState = Object.assign({}, state)

	switch (action.type) {
		case SET_DEVICE:
			newState.device = action.value
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
			return newState
	}
	return state
}

export default reducer
