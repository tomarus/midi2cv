import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'

export default ((props) =>
	<FormGroup>
		<FormControl componentClass='select' value={props.transpose}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={-1} value={-1}>Unknown</option>
			{[...Array(127).keys()].map((index) =>
				<option key={index+1} value={index+1}>{index - 63}</option>
			)}
		</FormControl>
	</FormGroup>
)
