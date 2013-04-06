#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

namespace Colour {
	enum Type {
		TEXT1,
		TEXT2,
		GRAPH_BORDER
	};
}

class CAppOptions {
public:
	sf::Color GetColourOf( Colour::Type colourType );
	std::string GetFontFilename();
	std::string GetHDDName();

	float GetUpdateInterval();
	float GetForcedSleep();

	bool ShowLink();

	void LoadAllOptions();

private:
	std::string GetSingleOption( std::string optionName );
	float GetSingleOptionAsFloat( std::string optionName );

	sf::Color m_text1_colour, m_text2_colour, m_graphBorder_colour;
	std::string m_font_filename, m_hdd_name, m_showLink;
	float m_updateInterval, m_forcedSleep;
};