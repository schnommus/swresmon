#pragma once

#include "CGraphControl.h"
#include "CTextControl.h"

struct Graph_CPU : public CGraphControl {
	Graph_CPU(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return m_app->SystemData().CPU_UsagePercent(); }
};

struct Graph_RAM : public CGraphControl {
	Graph_RAM(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return m_app->SystemData().RAM_UsagePercent(); }
};

struct Text_CPU_UsagePercent : public CTextControl {
	Text_CPU_UsagePercent( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().CPU_UsagePercent() << "%"; }
};

struct Text_CPU_Load : public CTextControl {
	Text_CPU_Load( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "CPU Load"; }
};

struct Text_RAM_Rotated : public CTextControl {
	Text_RAM_Rotated( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { m_text.setRotation(-90); }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "RAM"; }
};

struct Text_RAM_UsagePercent_Rotated : public CTextControl {
	Text_RAM_UsagePercent_Rotated( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { m_text.setRotation(-90); }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_UsagePercent() << "%"; }
};

struct Text_HDD_Usage_Title : public CTextControl {
	Text_HDD_Usage_Title( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "HDD Usage: (" << m_app->Options().GetHDDName() << ")"; }
};

struct Text_HDD_GigsWritten : public CTextControl {
	Text_HDD_GigsWritten( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsWritten() << "Gb Written"; }
};

struct Text_HDD_GigsRead : public CTextControl {
	Text_HDD_GigsRead( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsRead() << "Gb Read"; }
};

struct Text_HDD_Usage : public CTextControl {
	Text_HDD_Usage( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsFree() << "Gb free of " << 
		m_app->SystemData().HDD_GigsFree() + m_app->SystemData().HDD_GigsUsed() << "Gb"; }
};

struct Text_UserName : public CTextControl {
	Text_UserName( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "User: " << m_app->SystemData().UserName(); }
};

struct Text_Uptime : public CTextControl {
	Text_Uptime( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Uptime: " << m_app->SystemData().Uptime() << "Hr"; }
};

struct Text_Chrono : public CTextControl {
	Text_Chrono( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().TimeString(); }
};

struct Text_SebLogo : public CTextControl {
	Text_SebLogo( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "sebholzapfel.com"; }
};

struct Screen_Classic : public IScreen {
	Screen_Classic() : IScreen("Screen_Classic") { }
	virtual void VPopulateControls() {
		AddControl( new Graph_CPU( 17, 450, 400, 270 ) );
		AddControl( new Text_CPU_UsagePercent( 65, 10, 90, Colour::TEXT1 ) );
		AddControl( new Text_CPU_Load( 220, 110, 24, Colour::TEXT2 ) );

		AddControl( new Graph_RAM( 445, 120, 280, 90 ) );
		AddControl( new Text_RAM_Rotated( 733, 112, 24, Colour::TEXT1 ) );
		AddControl( new Text_RAM_UsagePercent_Rotated( 763, 97, 18, Colour::TEXT2 ) );

		AddControl( new Text_HDD_Usage_Title( 470, 157, 26, Colour::TEXT1 ) );
		AddControl( new Text_HDD_GigsRead( 473, 194, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_GigsWritten( 473, 222, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_Usage( 473, 253, 16, Colour::TEXT2 ) );

		AddControl( new Text_UserName( 473, 323, 22, Colour::TEXT1 ) );
		AddControl( new Text_Uptime( 473, 353, 22, Colour::TEXT1 ) );
		AddControl( new Text_Chrono( 473, 445, 12, Colour::TEXT1 ) );

		AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};