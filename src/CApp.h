#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// Uncomment to instead render to a window (for debugging)
//#define EMULATE_SCREEN

class CApp {
public:
	CApp();

	void Initialize( int size_x, int size_y );

	void Run();

	inline float GetFrameTime();

	virtual ~CApp();

private:
	void RenderToSwitchblade();

	sf::RenderTexture m_renderSurface;

	// Sending images to the device
	sf::Image m_renderBufferImage;
	const unsigned char *m_renderBufferIn;
	unsigned short *m_renderBufferOut;

	// Keeping track of frame delta
	sf::Clock m_frameClock;
	float m_frameTime;

	// Only need a renderwindow if we're emulating the screen
#ifdef EMULATE_SCREEN
	sf::RenderWindow m_screenEmulator;
#endif
};

