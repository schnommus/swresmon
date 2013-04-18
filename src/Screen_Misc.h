#pragma once

#include "SharedControls.h"

struct Screen_Misc : public IScreen {
	Screen_Misc() : IScreen("MISC") { }
	virtual void VPopulateControls() {
		AddControl( new Text_Custom( 284, 13, 22, Colour::TEXT2, "Miscellaneous" ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};