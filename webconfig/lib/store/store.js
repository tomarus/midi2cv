import {createStore, applyMiddleware, combineReducers} from 'redux'
import thunk from 'redux-thunk'

import midiReducer from 'lib/store/midi'
import configReducer from 'lib/store/config'

function logger ({ getState }) {
	return (next) => (action) => {
		console.log('will dispatch', action)

		// Call the next dispatch method in the middleware chain.
		let returnValue = next(action)
		console.log('state after dispatch', getState())

		// This will likely be the action itself, unless
		// a middleware further in chain changed it.
		return returnValue
	}
}

var reducers = combineReducers({
	midi: midiReducer,
	config: configReducer
})

var store = createStore(
	reducers,
	applyMiddleware(thunk)
)

export default store
