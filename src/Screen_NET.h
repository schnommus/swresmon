#pragma once

#include "SharedControls.h"

struct Screen_NET : public IScreen {
	Screen_NET() : IScreen("NET") { }
	virtual void VPopulateControls() {
		AddControl( new Text_Custom( 284, 13, 22, Colour::TEXT2, "Networking" ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};