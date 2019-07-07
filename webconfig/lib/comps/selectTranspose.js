import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'

export default ((props) =>
	<FormGroup>
		<FormControl componentClass='select' value={props.transpose}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={0} value={0}>Unknown</option>
			{[...Array(97).keys()].map((index) =>
				<option key={index - 48 + 64} value={index - 48 + 64}>{index - 48}</option>
			)}
		</FormControl>
	</FormGroup>
)
