import React from 'react'
import {Col, Panel} from 'react-bootstrap'
import {connect} from 'react-redux'

import ConfigTable from 'lib/panels/config/configTable'

const mapStateToProps = (state) => {
	return {
		inputs: state.midi.inputs
	}
}

const ConfigPanelHeader = () =>
	<div className='row no-gutter'>
		<Col xs={12}><span className='panel-header'>Setup Configuration</span></Col>
	</div>


export default connect(mapStateToProps)((props) =>
	<div>
		<ConfigTable/>
	</div>
)
