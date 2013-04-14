#pragma once

#include "SharedControls.h"

struct Screen_BigClock : public IScreen {
	Screen_BigClock() : IScreen("Screen_BigClock") { }
	virtual void VPopulateControls() {

		AddControl( new Text_Chrono( 25, 212, 44, Colour::TEXT1 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};