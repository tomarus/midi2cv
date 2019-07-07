import React from 'react'
import { FormControl, FormGroup } from 'react-bootstrap'

export default ((props) =>
	<FormGroup bsSize={props.bsSize}>
		<FormControl componentClass='select' value={props.channel}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={0} value={0}>Unknown</option>
			{[...Array(16).keys()].map((index) =>
				<option key={index} value={index + 1}>{index + 1}</option>
			)}
		</FormControl>
	</FormGroup>
)
