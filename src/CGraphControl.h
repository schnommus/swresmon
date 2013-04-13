#pragma once

#include "CApp.h"
#include "IUpdatedControl.h"
#include <deque>

class CGraphControl : public IUpdatedControl {
public:
	CGraphControl( int pos_x, int pos_y, int width, int height, int maxReadings, int upperThreshold );

	virtual void VInit();

	virtual float VUpdateGraph();

	virtual void VUpdateControl();

	virtual void VStep();

	virtual void VDraw();

	virtual void VDestroy();

private:
	std::deque<float> m_data;
	sf::Vector2f m_graphSize;
	int m_maxReadings;
	int m_upperThreshold;

	//Still slide when not updating
	float m_slideValue;
};
