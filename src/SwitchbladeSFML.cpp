#include <iostream>

#include "CApp.h"
#include "CSystemGraphs.h"


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddControl(new CGraphCPU( 17, 450, 400, 270 ) );
	app.AddControl(new CGraphRAM( 445, 120, 280, 90 ) );

	// Don't put the graph onscreen for this one; it's just some text
	// TODO: Move into separate text control
	app.AddControl(new COtherStuff(0, 0, 1, 1));

	app.Run();

	return 0;
}