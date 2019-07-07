import React from 'react'
import { connect } from 'react-redux'

import { Col, Panel, Row, Table } from 'react-bootstrap'

import { SetConfigAddress, SetOutputDevice } from 'lib/midi/midi'

import SelectArpSync from 'lib/comps/selectArpSync'
import SelectChannel from 'lib/comps/selectChannel'
import SelectControlChange from 'lib/comps/selectControlChange'
import SelectNote from 'lib/comps/selectNote'
import SelectNumber from 'lib/comps/selectNumber'
import SelectOutputDevice from 'lib/comps/selectOutputDevice'
import SelectTranspose from 'lib/comps/selectTranspose'

const mapStateToProps = (state) => {
	return {
		device: state.config.device,
		split: state.config.split,
		ch1: state.config.channel1,
		ch2: state.config.channel2,
		transpose1: state.config.transpose1,
		transpose2: state.config.transpose2,
		cc1: state.config.cc1,
		cc2: state.config.cc2,
		ccch1: state.config.ccchannel1,
		ccch2: state.config.ccchannel2,
		pitchbend1: state.config.pitchbend1,
		pitchbend2: state.config.pitchbend2,
		midi1sync: state.config.midi1sync,
		midi2sync: state.config.midi2sync,
		clockticks: state.config.clockticks
	}
}

const mapDispatchToProps = (dispatch) => ({
	handleSplit(split) { SetConfigAddress(1, split) },                            // addr 0x01
	handleChannel(index, channel) { SetConfigAddress(1 + index, channel) },       // addr 0x02
	handleTranspose(index, transpose) { SetConfigAddress(3 + index, transpose) }, // addr 0x04
	handleCC(index, control) { SetConfigAddress(5 + index, control) },            // addr 0x06
	handleCCChannel(index, channel) { SetConfigAddress(7 + index, channel) },     // addr 0x08
	handlePitchbend(index, pitchbend) { SetConfigAddress(9 + index, pitchbend) }, // addr 0x0a
	handleArpSync(index, sync) { SetConfigAddress(11 + index, sync) },            // addr 0x0c
	handleClockSync(index, sync) { SetConfigAddress(14, sync) },                  // addr 0x0e
	handleOutputDevice(device) { SetOutputDevice(device) }
})

const Channel = connect(mapStateToProps, mapDispatchToProps)((props) =>
	<Panel header={<span className='panel-header'>CV + Gate Output {props.index}</span>}>
		<Row>
			<Col xs={6}>MIDI Channel</Col>
			<Col xs={6}><SelectChannel index={props.index} channel={props.ch} onChange={props.handleChannel} /></Col>
		</Row>
		<Row>
			<Col xs={6}>Transpose</Col>
			<Col xs={6}><SelectTranspose index={props.index} transpose={props.transpose} onChange={props.handleTranspose} /></Col>
		</Row>
		<Row>
			<Col xs={6}>Pitchbend nr of notes</Col>
			<Col xs={6}><SelectNumber min={0} max={24} index={props.index} number={props.pitchbend} onChange={props.handlePitchbend} /></Col>
		</Row>
		<Row>
			<Col xs={6}>Arpeggiator Speed clockticks</Col>
			<Col xs={6}><SelectArpSync index={props.index} sync={props.sync} onChange={props.handleArpSync} /></Col>
		</Row>
	</Panel>
)

const Control = connect(mapStateToProps, mapDispatchToProps)((props) =>
	<Panel header={<span className='panel-header'>Control Change Output {props.index}</span>}>
		<Row>
			<Col xs={6}>MIDI Channel</Col>
			<Col xs={6}><SelectChannel index={props.index} channel={props.ch} onChange={props.handleCCChannel} /></Col>
		</Row>
		<Row>
			<Col xs={6}>Control Change</Col>
			<Col xs={6}><SelectControlChange index={props.index} value={props.cc} onChange={props.handleCC} /></Col>
		</Row>
	</Panel>
)

export default connect(mapStateToProps, mapDispatchToProps)((props) =>
	<div>
		<Panel header={<span className='panel-header'>Global Options</span>}>
			<Row>
				<Col xs={6}>Webconfig Output Device</Col>
				<Col xs={6}><SelectOutputDevice device={props.device} onChange={props.handleOutputDevice} /></Col>
			</Row>
			<Row>
				<Col xs={6}>Split at Note</Col>
				<Col xs={6}><SelectNote note={props.split} onChange={props.handleSplit} /></Col>
			</Row>
			<Row>
				<Col xs={6}>Clock Divider MIDI Clock Ticks</Col>
				<Col xs={6}><SelectNumber min={1} max={96} index={0} number={props.clockticks} onChange={props.handleClockSync} /></Col>
			</Row>
		</Panel>

		<Channel index={1} ch={props.ch1} transpose={props.transpose1} pitchbend={props.pitchbend1} sync={props.midi1sync}/>
		<Channel index={2} ch={props.ch2} transpose={props.transpose2} pitchbend={props.pitchbend2} sync={props.midi2sync}/>
		<Control index={1} ch={props.ccch1} cc={props.cc1}/>
		<Control index={2} ch={props.ccch2} cc={props.cc2}/>
	</div>
)