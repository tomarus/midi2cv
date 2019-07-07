import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'
import {connect} from 'react-redux'
import data from 'lib/midi/data'

const mapStateToProps = (state, props) => ({
	inputs: state.midi.inputs
})

const hex = val => {
	let hex = val.toString(16)
	while (hex.length < 2) hex = '0' + hex
	return '0x' + hex
}

export default connect(mapStateToProps)((props) =>
	<FormGroup bsSize={props.bsSize}>
		<FormControl componentClass='select' value={props.value}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={-1} value={-1}>Unknown</option>
			{data.Controllers.map((input, index) =>
				<option key={index} value={index}>{hex(index)} - {input}</option>
			)}
		</FormControl>
	</FormGroup>
)
