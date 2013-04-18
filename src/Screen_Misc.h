#pragma once

#include "SharedControls.h"

struct Screen_Misc : public IScreen {
	Screen_Misc() : IScreen("MISC") { }
	virtual void VPopulateControls() {
		
		AddControl( new Text_UserName( 542, 169, 22, Colour::TEXT1 ) );
		AddControl( new Text_Uptime( 542, 236, 22, Colour::TEXT1 ) );

		AddControl( new Text_Custom( 30, 75, 40, Colour::TEXT1, "OS" ) );
		AddControl( new Text_Custom( 30, 125, 22, Colour::TEXT1, "Name: " + m_app->SystemData().m_OS_Desc) );
		AddControl( new Text_Custom( 30, 160, 22, Colour::TEXT1, "Codename: " + m_app->SystemData().m_OS_Codename ) );
		AddControl( new Text_Custom( 30, 195, 22, Colour::TEXT2, "Patch Level: " + m_app->SystemData().m_OS_PatchLevel) );
		AddControl( new Text_Custom( 30, 230, 22, Colour::TEXT2, "Base Version: " + m_app->SystemData().m_OS_BaseVersion ) );
		AddControl( new Text_Custom( 30, 265, 22, Colour::TEXT2, "Base Name: " + m_app->SystemData().m_OS_BaseName ) );
		AddControl( new Text_Custom( 30, 300, 22, Colour::TEXT2, "Endianness: " + m_app->SystemData().m_OS_CPU_Endianness) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};