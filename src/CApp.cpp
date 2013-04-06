#include "CApp.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SwitchBlade.h>

CApp::CApp() : m_ofs("SwitchbladeSFMLAppLog.txt")
#ifdef EMULATE_SCREEN
	// Res-dependent as it has to know on init. For debugging though so eh.
	// + I don't think Razer'll be changing their device res any time soon
	,m_screenEmulator( sf::VideoMode(800, 480), "Emulated Switchblade Screen" )
#endif
{
	m_renderBufferOut = nullptr;
}


CApp::~CApp() {
	delete[] m_renderBufferOut;
}


void CApp::Initialize( int size_x, int size_y ) {
	// Redirect standard out to a logfile
	std::cout.rdbuf(m_ofs.rdbuf());
	
	// Create the render surface
	std::cout << "Creating SFML render surface..." << std::endl;
	if ( !m_renderSurface.create( size_x, size_y ) ) {
		throw std::exception("Failed to create render surface");
	}

#ifndef EMULATE_SCREEN
	// Connect to switchblade device
	std::cout << "Hooking to Switchblade..." << std::endl;
	if( RzSBStart() != RZSB_OK ) {
		throw std::exception("Couldn't connect to switchblade device");
	}
#endif

	// Stores RGB565 info before being sent to the switchblade device
	m_renderBufferOut = new unsigned short[m_renderSurface.getSize().x * m_renderSurface.getSize().y];

	m_options.LoadAllOptions();
}


void CApp::Run() {
	bool running = true;
	while( running ) {
		// To avoid hogging CPU
		sf::sleep( sf::seconds( m_options.GetForcedSleep() ) );

		// BEGIN LOGIC

		for( int i = 0; i != m_controls.size(); ++i ) {
			m_controls[i]->VStep();
		}

#ifdef EMULATE_SCREEN
		sf::Event e;
		while ( m_screenEmulator.pollEvent(e) ) {
			if( e.type == sf::Event::Closed) {
				running = false;
				m_screenEmulator.close();
			}
		}
#endif

		// END LOGIC

		m_renderSurface.clear();

		// BEGIN DRAWING

		for( int i = 0; i != m_controls.size(); ++i ) {
			m_controls[i]->VDraw();
		}

#ifdef SHOW_FPS
		// Show framerate
		std::ostringstream iss; iss << int(1/m_frameTime) << " FPS";
		sf::Text t( iss.str(), sf::Font::getDefaultFont(), 10 );
		m_renderSurface.draw(t);
#endif

		// END DRAWING

		m_renderSurface.display();

		// Copy the render surface to an image, get a pointer to the raw pixels
		m_renderBufferImage = m_renderSurface.getTexture().copyToImage();
		m_renderBufferIn = m_renderBufferImage.getPixelsPtr();

#ifndef EMULATE_SCREEN
		// Finally, send the data to the device
		RenderToSwitchblade();
#else
		m_screenEmulator.clear();
		m_screenEmulator.draw(sf::Sprite(m_renderSurface.getTexture()));
		m_screenEmulator.display();
#endif

		// Keep track of frame time
		m_frameTime = m_frameClock.getElapsedTime().asSeconds();
		m_frameClock.restart();
	}

#ifndef EMULATE_SCREEN
	RzSBStop();
#endif
}


float CApp::GetFrameTime() {
	return m_frameTime;
}


sf::RenderTexture &CApp::RenderSurface() {
	return m_renderSurface;
}

CAppOptions &CApp::Options() {
	return m_options;
}


void CApp::AddControl( IControl *control ) {
	m_controls.push_back( std::shared_ptr<IControl>(control) );
	m_controls.back()->m_app = this;
	m_controls.back()->VInit();
}

void CApp::RenderToSwitchblade() {
	// Convert from 32-bit RGBA to 16-bit RGB565 with some bit-flipping
	const sf::Vector2u sz(m_renderSurface.getSize());
	for( long i = 0; i != sz.x*sz.y; ++i ) {
		int xpos = i%sz.x, ypos = i/sz.x;
		// Shift bits to their positions, then mask to pixel for each colour
		m_renderBufferOut[i] = 0x1F & m_renderBufferIn[sz.x*ypos*4+xpos*4+2]>>3;
		m_renderBufferOut[i] |= 0x7E0 & m_renderBufferIn[sz.x*ypos*4+xpos*4+1]<<3;
		m_renderBufferOut[i] |= 0xF800 & m_renderBufferIn[sz.x*ypos*4+xpos*4]<<8;
	}

	// Set up buffer parameters
	RZSBSDK_BUFFERPARAMS params;
	params.PixelType = RGB565;
	params.DataSize = sz.x*sz.y*2;
	params.pData = reinterpret_cast<unsigned char*>(m_renderBufferOut);

	// Then do the actual sending
	RzSBRenderBuffer(RZSBSDK_DISPLAY_WIDGET, &params );
}