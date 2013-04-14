#include <iostream>

#include "CApp.h"
#include "CSystemGraphs.h"
#include "CTextControl.h"


struct Text_CPU_UsagePercent : public CTextControl {
	Text_CPU_UsagePercent( int x, int y ) : CTextControl(x, y, 90, Colour::TEXT1) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().CPU_UsagePercent() << "%"; }
};

struct Text_CPU_Load : public CTextControl {
	Text_CPU_Load( int x, int y ) : CTextControl(x, y, 24, Colour::TEXT2) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "CPU Load"; }
};

// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddControl( new CGraphCPU( 17, 450, 400, 270 ) );
	app.AddControl( new CGraphRAM( 445, 120, 280, 90 ) );

	app.AddControl( new Text_CPU_UsagePercent( 65, 10 ) );
	app.AddControl( new Text_CPU_Load( 220, 110 ) );
	// Don't put the graph onscreen for this one; it's just some text
	// TODO: Move into separate text control
	app.AddControl( new COtherStuff(0, 0, 1, 1) );

	app.Run();

	return 0;
}