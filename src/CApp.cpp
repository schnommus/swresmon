#include "CApp.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SwitchBlade.h>

// Init running here so that the app will still quit if it receives a 'disable' event during initialization
bool CApp::m_isrunning = true;


CApp::CApp() : m_ofs("SwitchbladeSFMLAppLog.txt")
#ifdef EMULATE_SCREEN
	// Res-dependent as it has to know on init. For debugging though so eh.
	// + I don't think Razer'll be changing their device res any time soon
	,m_screenEmulator( sf::VideoMode(800, 480), "Emulated Switchblade Screen" )
#endif
{ }


CApp::~CApp() { }


#ifndef EMULATE_SCREEN
// This function never seems to get called even though it's registered but I'll leave it here :/
HRESULT __stdcall RazerAppEventCallback( RZSBSDK_EVENTTYPETYPE eType, DWORD i1, DWORD i2) {
	std::cout << "Got event from RazorSDK: " << eType << std::endl;

	// Easier just to kill the app on any closing events, it re-loads pretty quick anyways.
	if( eType == RZSBSDK_EVENT_DEACTIVATED || eType == RZSBSDK_EVENT_CLOSE || eType == RZSBSDK_EVENT_EXIT ) {
		CApp::KillApplication();
	}
	return RZSB_OK;
}
#endif


void CApp::Initialize( int size_x, int size_y ) {
	try {

	// Redirect standard out to a logfile
	std::cout.rdbuf(m_ofs.rdbuf());
	
	// Create the render surface
	std::cout << "Creating SFML render surface..." << std::endl;
	m_virtualRenderSurface.Init( size_x, size_y );

#ifndef EMULATE_SCREEN
	// Connect to switchblade device
	std::cout << "Hooking to Switchblade..." << std::endl;

	HRESULT rval = RzSBStart();
	if( rval != RZSB_OK ) {
		std::ostringstream oss;
		oss << "Couldn't connect to switchblade device! Code " << std::hex << rval << std::endl;
		throw std::exception(oss.str().c_str());
	}

	// To handle app-switch events etc
	std::cout << "Registering to RzAppEvents returned code " << std::hex << RzSBAppEventSetCallback( &RazerAppEventCallback ) << std::endl;
#endif

	m_options.LoadAllOptions();

	m_systemData.Init();

	} catch (std::exception &e) {
		std::cout << "Fatal exception: " << e.what() << std::endl;
		KillApplication();
	} catch (...) {
		// Shouldn't happen
		std::cout << "Anonymous fatal exception!" << std::endl;
		KillApplication();
	}
}


void CApp::Run() {
	while( m_isrunning ) {

		// BEGIN LOGIC

		m_systemData.Step();

		for( int i = 0; i != m_screens.size(); ++i ) {
			m_screens[i]->StepControls();
		}

#ifdef EMULATE_SCREEN
		sf::Event e;
		while ( m_screenEmulator.pollEvent(e) ) {
			if( e.type == sf::Event::Closed) {
				m_screenEmulator.close();
				KillApplication();
			}
		}
#endif

		// END LOGIC

		m_virtualRenderSurface.RenderSurface().clear();

		// BEGIN DRAWING

		for( int i = 0; i != m_screens.size(); ++i ) {
			if( m_screens[i]->m_name == m_activeScreenName)
				m_screens[i]->DrawControls();
		}

#ifdef SHOW_FPS
		// Show framerate
		std::ostringstream iss; iss << int(1/m_frameTime) << " FPS";
		sf::Text t( iss.str(), sf::Font::getDefaultFont(), 10 );
		m_virtualRenderSurface.RenderSurface().draw(t);
#endif

		// END DRAWING

		m_virtualRenderSurface.RenderSurface().display();


#ifndef EMULATE_SCREEN
		// Finally, send the data to the device
		RenderToSwitchblade();
#else
		m_screenEmulator.clear();
		m_screenEmulator.draw(sf::Sprite(m_virtualRenderSurface.RenderSurface().getTexture()));
		m_screenEmulator.display();
#endif

		// To avoid hogging CPU
		sf::sleep( sf::seconds( m_options.GetForcedSleep() ) );

		// Keep track of frame time
		m_frameTime = m_frameClock.getElapsedTime().asSeconds();
		m_frameClock.restart();
	}

	m_systemData.Destroy();

#ifndef EMULATE_SCREEN
	RzSBStop();
#endif
}


float CApp::GetFrameTime() {
	return m_frameTime;
}

sf::RenderTexture &CApp::RenderSurface() {
	return m_virtualRenderSurface.RenderSurface();
}

CSystemData &CApp::SystemData() {
	return m_systemData;
}

CAppOptions &CApp::Options() {
	return m_options;
}

void CApp::KillApplication() {
	m_isrunning = false;
}


void CApp::AddScreen( IScreen *screen ) {
	m_screens.push_back( std::shared_ptr<IScreen>(screen) );
	m_screens.back()->m_app = this;
	m_screens.back()->VPopulateControls();
}

void CApp::SetActiveScreen( std::string name ) {
	m_activeScreenName = name;
}


void CApp::RenderToSwitchblade() {
#ifndef EMULATE_SCREEN
	const sf::Vector2u sz( m_virtualRenderSurface.RenderSurface().getSize() );

	// Set up buffer parameters
	RZSBSDK_BUFFERPARAMS params;
	params.PixelType = RGB565;
	params.DataSize = sz.x*sz.y*2;
	params.pData = reinterpret_cast<unsigned char*>( m_virtualRenderSurface.GetRGB565() );

	// Then do the actual sending
	HRESULT rval = RzSBRenderBuffer(RZSBSDK_DISPLAY_WIDGET, &params );
	if( rval != RZSB_OK ) {
		std::cout << "Error " << std::hex << rval << " when writing to render buffer! Most likely app is no longer active. Exiting...";
		KillApplication();
	}
#endif
}