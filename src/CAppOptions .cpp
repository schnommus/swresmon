#include "CAppOptions.h"

#include <sstream>

sf::Color CAppOptions::GetColourOf( Colour::Type colourType ) {
	switch( colourType ) {
		case Colour::TEXT1:
			return m_text1_colour;
		case Colour::TEXT2:
			return m_text2_colour;
		case Colour::GRAPH_BORDER:
			return m_graphBorder_colour;
	}
}

std::string CAppOptions::GetFontFilename() {
	return m_font_filename;
}

void CAppOptions::LoadAllOptions() {
	m_text1_colour = sf::Color( GetSingleOptionAsFloat("Text1_Red"), GetSingleOptionAsFloat("Text1_Green"), GetSingleOptionAsFloat("Text1_Blue"), GetSingleOptionAsFloat("Text1_Alpha") );
	m_text2_colour = sf::Color( GetSingleOptionAsFloat("Text2_Red"), GetSingleOptionAsFloat("Text2_Green"), GetSingleOptionAsFloat("Text2_Blue"), GetSingleOptionAsFloat("Text2_Alpha") );
	m_graphBorder_colour = sf::Color( GetSingleOptionAsFloat("GraphBorder_Red"), GetSingleOptionAsFloat("GraphBorder_Green"), GetSingleOptionAsFloat("GraphBorder_Blue"), GetSingleOptionAsFloat("GraphBorder_Alpha") );

	m_font_filename = GetSingleOption("FontName");
}


std::string CAppOptions::GetSingleOption( std::string optionName ) {
	std::ifstream ifs;
	ifs.open(std::string("SwResMon.cfg"), std::ios::in);
	if( !ifs.is_open() ) {
		throw std::exception("Couldn't open configuration file: SwResMon.cfg");
	}

	while( !ifs.eof() ) {
		std::string all; getline(ifs, all);
		std::string n, msg;
		if ( all.find('=') != std::string::npos) // If there's an '='
			n = all.substr(0, all.find('=')), msg = all.substr(all.find('=')+1, all.size()-1 );

		if( n == optionName ) {
			ifs.close();
			return msg;
		}
	}

	ifs.close();
	return "";
}



float CAppOptions::GetSingleOptionAsFloat( std::string optionName ) {
	std::istringstream iss( GetSingleOption( optionName ) );
	float f; iss >> f;
	return f;
}