import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'

export default ((props) =>
	<FormGroup>
		<FormControl componentClass='select' value={props.number}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={-1} value={-1}>Unknown</option>
			{[...Array(props.max-props.min+1).keys()].map((index) =>
				<option key={index} value={index+props.min}>{index+props.min}</option>
			)}
		</FormControl>
	</FormGroup>
)
