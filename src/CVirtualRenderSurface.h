#pragma once

#include <SFML/Graphics.hpp>

class CVirtualRenderSurface {
public:
	CVirtualRenderSurface();
	~CVirtualRenderSurface();

	sf::RenderTexture &RenderSurface();

	void Init( int size_x, int size_y );

	unsigned short *GetRGB565();

private:
	sf::RenderTexture m_renderSurface;

	sf::Image m_renderBufferImage;
	const unsigned char *m_renderBufferIn;
	unsigned short *m_renderBufferOut;
};