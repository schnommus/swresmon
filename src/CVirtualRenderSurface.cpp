#include "CVirtualRenderSurface.h"

CVirtualRenderSurface::CVirtualRenderSurface() {
	m_renderBufferOut = nullptr;
}

CVirtualRenderSurface::~CVirtualRenderSurface() {
	delete[] m_renderBufferOut;
}

void CVirtualRenderSurface::Init( int size_x, int size_y ) {
	if ( !m_renderSurface.create( size_x, size_y ) ) {
		throw std::exception("Failed to create render surface");
	}

	// Stores RGB565 info
	m_renderBufferOut = new unsigned short[m_renderSurface.getSize().x * m_renderSurface.getSize().y];
}

sf::RenderTexture &CVirtualRenderSurface::RenderSurface() {
	return m_renderSurface;
}

unsigned short *CVirtualRenderSurface::DoRGB565Conversion() {
	m_renderBufferIn = m_renderBufferImage.getPixelsPtr();

	// Convert from 32-bit RGBA to 16-bit RGB565 with some bit-flipping
	const sf::Vector2u sz(m_renderBufferImage.getSize());
	for( long i = 0; i != sz.x*sz.y; ++i ) {
		int xpos = i%sz.x, ypos = i/sz.x;
		// Shift bits to their positions, then mask to pixel for each colour
		m_renderBufferOut[i] = 0x1F & m_renderBufferIn[sz.x*ypos*4+xpos*4+2]>>3;
		m_renderBufferOut[i] |= 0x7E0 & m_renderBufferIn[sz.x*ypos*4+xpos*4+1]<<3;
		m_renderBufferOut[i] |= 0xF800 & m_renderBufferIn[sz.x*ypos*4+xpos*4]<<8;
	}
	return m_renderBufferOut;
}

// Will probably add a second method that subdivides into images (for dynamic keys)
unsigned short *CVirtualRenderSurface::GetRGB565() {
	// Copy the render surface to an image, get a pointer to the raw pixels
	m_renderBufferImage = m_renderSurface.getTexture().copyToImage();
	return DoRGB565Conversion();
}

unsigned short *CVirtualRenderSurface::GetSubsectionRGB565( int pos_x, int pos_y, int size_x, int size_y ) {
	m_renderBufferImage.create( size_x, size_y );
	m_renderBufferImage.copy( m_renderSurface.getTexture().copyToImage(), 0, 0, sf::IntRect( pos_x, pos_y, size_x, size_y ) );
	return DoRGB565Conversion();
}

sf::Image CVirtualRenderSurface::GetSubsectionAsImage( int pos_x, int pos_y, int size_x, int size_y ) {
	m_renderBufferImage.create( size_x, size_y );
	m_renderBufferImage.copy( m_renderSurface.getTexture().copyToImage(), 0, 0, sf::IntRect( pos_x, pos_y, size_x, size_y ) );
	return m_renderBufferImage;
}