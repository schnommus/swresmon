#pragma once

#include "SharedControls.h"

struct Screen_All : public IScreen {
	Screen_All() : IScreen("ALL #1") { }
	virtual void VPopulateControls() {
		AddControl( new Graph_CPU( 46, 107, 700, 90 ) );
		AddControl( new Graph_RAM( 46, 222, 700, 90 ) );
		AddControl( new Graph_NET( 46, 335, 700, 90 ) );
		AddControl( new Graph_HDD( 46, 450, 700, 90 ) );

		AddControl( new Text_Custom_Rotated( 15, 88, 22, Colour::TEXT1, "CPU" ) );
		AddControl( new Text_Custom_Rotated( 15, 210, 22, Colour::TEXT1, "RAM" ) );
		AddControl( new Text_Custom_Rotated( 15, 315, 22, Colour::TEXT1, "NET" ) );
		AddControl( new Text_Custom_Rotated( 15, 436, 22, Colour::TEXT1, "HDD" ) );

		AddControl( new Text_UserName_Rotated( 765, 222, 18, Colour::TEXT2 ) );
		AddControl( new Text_Uptime_Rotated( 765, 436, 18, Colour::TEXT2 ) );

		AddControl( new Text_Chrono( 638, 462, 10, Colour::TEXT1) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};