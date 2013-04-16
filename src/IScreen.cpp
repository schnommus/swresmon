#include "IScreen.h"
#include "CApp.h"

#include <SFML/Graphics.hpp>
#include <sstream>

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

#ifdef MOVE_CONTROLS // Here instead of step because draw is only called on active screens.
	for( int i = 0; i != m_controls.size(); ++i ) {
		const int distanceThreshhold = 10;

		sf::Vector2i pos = sf::Mouse::getPosition( m_app->m_screenEmulator ); 
		sf::Vector2f pos2 = m_controls[i]->Position();
		float dist = sqrt( pow( pos.x-pos2.x, 2 ) + pow( pos.y-pos2.y, 2 ) );
		if( dist < distanceThreshhold ) {
			if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
				m_controls[i]->Position().x = pos.x;
				m_controls[i]->Position().y = pos.y;
			}

			std::ostringstream oss; oss << "x=" << m_controls[i]->Position().x << " y=" << m_controls[i]->Position().y;
			sf::Text t(oss.str(), sf::Font::getDefaultFont(), 12 );
			t.setPosition(pos.x+10, pos.y);
			m_app->RenderSurface().draw(t);
		}

		sf::CircleShape c(distanceThreshhold);
		c.setOrigin(c.getLocalBounds().width/2, c.getLocalBounds().height/2);
		c.setFillColor( sf::Color(0, 0, 0, 0) );
		c.setOutlineColor( sf::Color(255, 255, 255, dist < distanceThreshhold? 255:128 ) );
		c.setOutlineThickness(2);
		c.setPosition(pos2.x, pos2.y);
		m_app->RenderSurface().draw(c);
	}
#endif
}

void IScreen::AddControl( IControl *control ) {
	m_controls.push_back( std::shared_ptr<IControl>(control) );
	m_controls.back()->m_app = m_app;
	m_controls.back()->VInit();
}