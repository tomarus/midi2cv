import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'

export default ((props) =>
	<FormGroup>
		<FormControl componentClass='select' value={props.transpose}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={-1} value={-1}>Unknown</option>
			<option key={0} value={0}>Use Potentiometer</option>
			{[...Array(96).keys()].map((index) =>
				<option key={index + 1} value={index + 1}>{index + 1}</option>
			)}
		</FormControl>
	</FormGroup>
)
