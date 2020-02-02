import React from 'react'
import {FormControl, FormGroup} from 'react-bootstrap'

import data from 'lib/midi/data'

export default ((props) =>
	<FormGroup>
		<FormControl componentClass='select' value={props.trigger} disabled={props.disabled}
			onChange={(e) => { props.onChange(props.index, parseInt(e.target.value, 10)) }}>
			<option key={-1} value={-1}>Unknown</option>
			{data.GMPercussion.map((value, index) =>
				<option key={index + 35} value={index + 35}>{index + 35}: {value}</option>
			)}
		</FormControl>
	</FormGroup>
)
