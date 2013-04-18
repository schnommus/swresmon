#pragma once

#include "SharedControls.h"

struct Screen_RAM : public IScreen {
	Screen_RAM() : IScreen("RAM") { }
	virtual void VPopulateControls() {
		AddControl( new Graph_RAM(45, 264, 700, 110) );
		AddControl( new Text_RAM_UsagePercent(284, 13, 100, Colour::TEXT1 ) );
		AddControl( new Text_Custom( 284, 13, 22, Colour::TEXT2, "RAM Used" ) );

		AddControl( new Text_RAM_MegsUsed(42, 318, 30, Colour::TEXT1 ) );
		AddControl( new Text_RAM_MegsFree(436, 318, 30, Colour::TEXT1 ) );
		AddControl( new Text_RAM_Total(226, 389, 20, Colour::TEXT1 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};