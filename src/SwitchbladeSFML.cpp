#include <iostream>

#include "CApp.h"
#include "Screen_Classic.h"
#include "Screen_BigClock.h"
#include "Screen_HDD.h"
#include "Screen_CPU.h"
#include "Screen_RAM.h"
#include "Screen_Misc.h"
#include "Screen_NET.h"
#include "Screen_All.h"


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddScreen( new Screen_CPU );

	app.AddScreen( new Screen_HDD );

	app.AddScreen( new Screen_NET );

	app.AddScreen( new Screen_RAM );

	app.AddScreen( new Screen_Misc );

	app.AddScreen( new Screen_BigClock );

	app.AddScreen( new Screen_Classic );

	app.AddScreen( new Screen_All );

	app.SetActiveScreen( "ALL #1" );

	app.Run();

	return 0;
}