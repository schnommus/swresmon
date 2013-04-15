#pragma once

#include <SFML/Graphics.hpp>

class CVirtualRenderSurface {
public:
	// Before any draw calls
	void Init( int size_x, int size_y );

	// For drawing to
	sf::RenderTexture &RenderSurface();

	unsigned short *GetRGB565();

	unsigned short *GetSubsectionRGB565( int pos_x, int pos_y, int size_x, int size_y );
	sf::Image GetSubsectionAsImage( int pos_x, int pos_y, int size_x, int size_y );

	CVirtualRenderSurface();
	~CVirtualRenderSurface();

private:
	unsigned short *DoRGB565Conversion();

	sf::RenderTexture m_renderSurface;

	sf::Image m_renderBufferImage;
	const unsigned char *m_renderBufferIn;
	unsigned short *m_renderBufferOut;
};