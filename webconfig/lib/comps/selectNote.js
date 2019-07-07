import React from 'react'
import {Button, ButtonGroup, Form, FormControl, FormGroup} from 'react-bootstrap'

import {Note} from 'lib/midi/util'

export default class extends React.Component {
	static propTypes = {
		note: React.PropTypes.number,
		onChange: React.PropTypes.func
	}

	state = {
		notes: [],
		note: 48
	}

	componentDidMount () {
		let notes = []
		notes.push((<option key={-1} value={-1}>Unknown</option>))
		notes.push((<option key={0} value={0}>No Split</option>))
		for (let i = 1; i<127; i++) {
			notes.push((<option key={i} value={i}>{Note(i)}</option>))
		}
		this.setState({notes, note: this.props.note})
	}

	componentWillReceiveProps (props) {
		if (props.note !== this.state.note) {
			this.setState({note: props.note})
		}
	}

	setNote (note) {
		if (note < 0 || note > 127) return
		this.setState({note})
		this.props.onChange(note)
	}

	handleChange = (event) => {
		let note = parseInt(event.target.value, 10)
		this.setNote(note)
	}

	render () {
		return (
			<FormGroup controlID='note'>
				<FormControl componentClass='select' value={this.state.note} onChange={this.handleChange}>
					{this.state.notes}
				</FormControl>
			</FormGroup>
		)
	}
}
