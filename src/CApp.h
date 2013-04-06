#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "IControl.h"

#include <vector>
#include <memory>
#include <fstream>

// Uncomment to instead render to a window (For debugging)
//#define EMULATE_SCREEN

//#define SHOW_FPS

class CApp {
public:
	CApp();

	void Initialize( int size_x, int size_y );

	void Run();

	void AddControl( IControl *control );

	sf::RenderTexture &RenderSurface();

	float GetFrameTime();

	virtual ~CApp();

private:
	void RenderToSwitchblade();

	sf::RenderTexture m_renderSurface;

	// Controls to be processed
	std::vector< std::shared_ptr< IControl > > m_controls;

	// Sending images to the device
	sf::Image m_renderBufferImage;
	const unsigned char *m_renderBufferIn;
	unsigned short *m_renderBufferOut;

	// Keeping track of frame delta
	sf::Clock m_frameClock;
	float m_frameTime;

	std::ofstream m_ofs;

	// Only need a renderwindow if we're emulating the screen
#ifdef EMULATE_SCREEN
	sf::RenderWindow m_screenEmulator;
#endif
};

