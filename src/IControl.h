#pragma once

#include <SFML/System.hpp>

class CApp;

class IControl {
public:
	friend class IScreen;

	IControl() : m_app(0) {}

	virtual void VInit() = 0;
	virtual void VStep() = 0;
	virtual void VDraw() = 0;
	virtual void VDestroy() = 0;

	sf::Vector2f &Position() { return m_position; }
	sf::Vector2f &Scale() { return m_scale; }
	float &Rotation() { return m_rotation; }

protected:
	// Will be assigned automatically when added to CApp instance
	// After the constructor is called. Do initialization in VInit();
	CApp *m_app;

	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	float m_rotation;
};