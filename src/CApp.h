#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "IScreen.h"
#include "CAppOptions.h"
#include "CSystemData.h"
#include "CVirtualRenderSurface.h"

#include <vector>
#include <memory>
#include <fstream>

// Uncomment to instead render to a window (For debugging)
#define EMULATE_SCREEN

//#define SHOW_FPS

class CApp {
public:
	CApp();

	void Initialize( int size_x, int size_y );

	void Run();

	void AddScreen( IScreen *screen );

	void SetActiveScreen( std::string name );

	sf::RenderTexture &RenderSurface();

	CSystemData &SystemData();

	CAppOptions &Options();

	float GetFrameTime();

	static void KillApplication();

	virtual ~CApp();

private:
	void RenderToSwitchblade();

	// Screens available in the app
	std::vector< std::shared_ptr< IScreen > > m_screens;
	std::string m_activeScreenName;

	// For rendering to the screen
	CVirtualRenderSurface m_virtualRenderSurface;

	// Keeping track of frame delta
	sf::Clock m_frameClock;
	float m_frameTime;

	// Logging
	std::ofstream m_ofs;

	// Config options
	CAppOptions m_options;

	// Keeps track of system stats
	CSystemData m_systemData;

	// Is the app running? (Static because nonmember must change this)
	static bool m_isrunning;

	// Only need a renderwindow if we're emulating the screen
#ifdef EMULATE_SCREEN
	sf::RenderWindow m_screenEmulator;
#endif
};

