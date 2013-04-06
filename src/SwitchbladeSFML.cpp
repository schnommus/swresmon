#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "CApp.h"

// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;
	app.Initialize(800, 480);
	app.Run();

	return 0;
}