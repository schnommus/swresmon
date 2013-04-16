#pragma once

#include "SharedControls.h"

struct Screen_HDD : public IScreen {
	Screen_HDD() : IScreen("HDD") { }
	virtual void VPopulateControls() {

		AddControl( new Text_HDD_Usage_Title( 470, 157, 26, Colour::TEXT1 ) );
		AddControl( new Text_HDD_GigsRead( 473, 194, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_GigsWritten( 473, 222, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_Usage( 473, 253, 16, Colour::TEXT2 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};