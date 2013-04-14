#include "CTextControl.h"

CTextControl::CTextControl( float xpos, float ypos, int characterSize, Colour::Type colour ) {
	m_position.x = xpos;
	m_position.y = ypos;
	m_charSize = characterSize;
	m_colourType = colour;
}

void CTextControl::VInit() {
	IUpdatedControl::VInit();
	m_colour = m_app->Options().GetColourOf(m_colourType);
	m_text.setCharacterSize(m_charSize);
	m_text.setPosition( m_position );
	m_text.setColor( m_colour );

	m_font.loadFromFile( m_app->Options().GetFontFilename() );
	m_text.setFont( m_font );
}

void CTextControl::VUpdateControl() {
	m_oss.str("");
	VUpdateText( m_oss );
	m_text.setString( m_oss.str() );
}

void CTextControl::VDraw() {
	m_app->RenderSurface().draw(m_text);
}