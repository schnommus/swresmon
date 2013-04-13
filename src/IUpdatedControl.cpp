#include "IUpdatedControl.h"
#include "CApp.h"

void IUpdatedControl::VStep() {
	if(m_updateClock.getElapsedTime().asSeconds() > m_updateInterval ) {
		VUpdateControl();
		m_updateClock.restart();
	}
}

void IUpdatedControl::VInit() {
	m_updateInterval = m_app->Options().GetUpdateInterval();
}