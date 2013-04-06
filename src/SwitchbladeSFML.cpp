#include <iostream>

#include "CApp.h"
#include "CSystemGraphs.h"


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {
	try {

	CApp app;

	app.Initialize(800, 480);

	app.AddControl(new CGraphCPU( 17, 450, 400, 270 ) );
	app.AddControl(new CGraphRAM( 445, 120, 280, 90 ) );

	// Don't put the graph onscreen for this one; it's just static text
	// tODO: Move into separate text control
	app.AddControl(new COtherStuff(2000, 2000, 1, 1));

	app.Run();

	} catch (std::exception &e) {
		std::cout << "Fatal exception: " << e.what() << std::endl;
	} catch (...) {
		// Shouldn't happen
		std::cout << "Anonymous fatal exception!" << std::endl;
	}

	return 0;
}