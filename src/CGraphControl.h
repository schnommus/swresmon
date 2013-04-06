#pragma once

#include "CApp.h"
#include <deque>

class CGraphControl : public IControl {
public:
	CGraphControl( int pos_x, int pos_y, int width, int height, int maxReadings, int upperThreshold, float updateInterval );

	virtual void VInit();

	virtual float VUpdateGraph();

	virtual void VStep();

	virtual void VDraw();

	virtual void VDestroy();

private:
	std::deque<float> m_data;
	sf::Vector2f m_graphSize;
	int m_maxReadings;
	int m_upperThreshold;
	float m_updateInterval;

	//Still slide when not updating
	float m_slideValue;

	sf::Clock m_updateClock;
};
