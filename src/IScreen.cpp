#include "IScreen.h"

IScreen::IScreen( std::string name ) {
	m_name = name;
}

void IScreen::StepControls() {
	for( int i = 0; i != m_controls.size(); ++i ) {
		m_controls[i]->VStep();
	}
}

void IScreen::DrawControls() {
	for( int i = 0; i != m_controls.size(); ++i ) {
		m_controls[i]->VDraw();
	}
}

void IScreen::AddControl( IControl *control ) {
	m_controls.push_back( std::shared_ptr<IControl>(control) );
	m_controls.back()->m_app = m_app;
	m_controls.back()->VInit();
}