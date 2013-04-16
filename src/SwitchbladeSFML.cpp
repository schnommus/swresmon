#include <iostream>

#include "CApp.h"
#include "Screen_Classic.h"
#include "Screen_BigClock.h"
#include "Screen_HDD.h"


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddScreen( new Screen_Classic );

	app.AddScreen( new Screen_HDD );

	app.AddScreen( new Screen_BigClock );

	app.SetActiveScreen( "CLASSIC" );

	app.Run();

	return 0;
}