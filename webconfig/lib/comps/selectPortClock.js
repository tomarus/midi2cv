import React from 'react'

export default ((props) =>
	<ul className="nav nav-pills">
		{[...Array(8).keys()].map((index) =>
			<li role="presentation" key={index} value={index + 1} className={'' + props.clock == index ? 'selected' : ''}>
				<a onClick={(e) => { props.onChange(props.index, index) }}>1/{1 << index}</a>
			</li>
		)}
	</ul>
)
