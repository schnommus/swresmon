#pragma once

#include "SharedControls.h"

struct Screen_All : public IScreen {
	Screen_All() : IScreen("ALL #1") { }
	virtual void VPopulateControls() {
		AddControl( new Graph_CPU( 17, 450, 400, 270 ) );
		//AddControl( new Text_CPU_UsagePercent( 65, 10, 90, Colour::TEXT1 ) );
		//AddControl( new Text_CPU_Load( 220, 110, 24, Colour::TEXT2 ) );

		AddControl( new Graph_RAM( 445, 120, 280, 90 ) );
		//AddControl( new Text_RAM_Rotated( 733, 112, 24, Colour::TEXT1 ) );
		AddControl( new Text_RAM_UsagePercent_Rotated( 763, 97, 18, Colour::TEXT2 ) );

		AddControl( new Text_HDD_Usage_Title( 470, 157, 26, Colour::TEXT1 ) );
		AddControl( new Text_HDD_GigsRead( 473, 194, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_GigsWritten( 473, 222, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_Usage( 473, 253, 16, Colour::TEXT2 ) );

		AddControl( new Text_UserName( 473, 323, 22, Colour::TEXT1 ) );
		AddControl( new Text_Uptime( 473, 353, 22, Colour::TEXT1 ) );
		AddControl( new Text_Chrono( 473, 442, 16, Colour::TEXT1 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};