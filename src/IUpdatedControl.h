#pragma once

#include "IControl.h"
#include <SFML\System.hpp>

class IUpdatedControl : public IControl {
public:

	virtual void VUpdateControl() = 0;

	virtual void VStep(); // These must be called by children

	virtual void VInit();

protected:
	float m_updateInterval;
	sf::Clock m_updateClock;
};