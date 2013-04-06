#include "CGraphControl.h"
#include <iostream>

CGraphControl::CGraphControl( int pos_x, int pos_y, int width, int height, int maxReadings, int upperThreshold, float updateInterval ) {
	m_position = sf::Vector2f( pos_x, pos_y );
	m_graphSize = sf::Vector2f( width, height );
	m_maxReadings = maxReadings;
	m_upperThreshold = upperThreshold;
	m_updateInterval = updateInterval;
}


void CGraphControl::VInit() {
	m_data.resize(m_maxReadings, 0);
}


float CGraphControl::VUpdateGraph() {
	return rand()%m_upperThreshold;
}


void CGraphControl::VStep() {
	// Don't update too often
	if(m_updateClock.getElapsedTime().asSeconds() > m_updateInterval ) {
		m_data.push_front(VUpdateGraph());
		m_data.resize(m_maxReadings, 0);
		m_slideValue = 0;
		m_updateClock.restart();
	}

	// Slide so the graph doesn't look jerky
	m_slideValue += ((m_graphSize.x/float(m_maxReadings))/(m_updateInterval))*m_app->GetFrameTime();
}


void CGraphControl::VDraw() {
	sf::VertexArray vertices(sf::LinesStrip, m_data.size());
	for( int i = 0; i != m_data.size(); ++i ) {
		vertices[i].position = m_position;
		vertices[i].position.y -= m_data[i]*(float(m_graphSize.y)/m_upperThreshold);
		vertices[i].position.x += float(i)*(m_graphSize.x/m_maxReadings)+m_slideValue;

		// Colour grading
		int colourGradient = m_data[i]/float(m_upperThreshold)*255;
		vertices[i].color = sf::Color(colourGradient, 0, 255-colourGradient );
		vertices[i].color.a = 128+colourGradient/2;

		// Make elements of value 0 disappear to remove pre-emptive trail
		if(m_data[i] <= 0.001) vertices[i].color.a = 0;
	}
	m_app->RenderSurface().draw(vertices);

	// So that ends are smooth, cover them with a rectangle
	sf::RectangleShape rect( sf::Vector2f((m_graphSize.x/m_maxReadings)*2, m_graphSize.y) );
	rect.setPosition( m_position.x, m_position.y-m_graphSize.y);
	rect.setFillColor(sf::Color::Black);
	m_app->RenderSurface().draw(rect);
	rect.setPosition( m_position.x+m_graphSize.x-(m_graphSize.x/m_maxReadings)*2+3, m_position.y-m_graphSize.y);
	m_app->RenderSurface().draw(rect);

	// Surround the control with a greyish bounding box
	sf::RectangleShape rect2( sf::Vector2f( m_graphSize.x, m_graphSize.y+10)  );
	rect2.setPosition( m_position.x+5, m_position.y-m_graphSize.y-5);
	rect2.setFillColor(sf::Color(0, 0, 0, 0));
	rect2.setOutlineColor(sf::Color(255, 255, 255, 30));
	rect2.setOutlineThickness(1);
	m_app->RenderSurface().draw(rect2);
}


void CGraphControl::VDestroy() {

}