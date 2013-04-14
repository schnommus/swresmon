#include <iostream>

#include "CApp.h"
#include "Screen_Classic.h"


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddScreen( new Screen_Classic );

	app.SetActiveScreen( "Screen_Classic" );

	app.Run();

	return 0;
}