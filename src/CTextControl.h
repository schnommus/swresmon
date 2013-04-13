#pragma once

#include "IUpdatedControl.h"
#include "CApp.h"
#include <string>
#include <sstream>

class CTextControl : public IUpdatedControl {
public:
	CTextControl( float xpos, float ypos, int characterSize, Colour::Type colour );

	virtual void VUpdateText( std::ostringstream &textstream ) { textstream << "<VUpdateText>"; };

	virtual void VInit();

	virtual void VUpdateControl();

	virtual void VDraw();

	virtual void VDestroy() { }

private:
	sf::Color m_colour;
	Colour::Type m_colourType;

	std::ostringstream m_oss;
	float m_charSize;
	sf::Text m_text;
};