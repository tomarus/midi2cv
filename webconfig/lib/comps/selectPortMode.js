import React from 'react'

export default ((props) =>
	<ul className="nav nav-pills">
		<li role="presentation" key={0} value={0} className={props.mode === 0 ? 'selected' : ''}>
			<a onClick={(e) => { props.onChange(props.index, 0) }}>Clock Divider</a>
		</li>
		<li role="presentation" key={1} value={1} className={props.mode === 1 ? 'selected' : ''}>
			<a onClick={(e) => { props.onChange(props.index, 1) }}>Drum Trigger</a>
		</li>
	</ul>
)
