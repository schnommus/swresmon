#pragma once

#include "SharedControls.h"

struct Screen_CPU : public IScreen {
	Screen_CPU() : IScreen("CPU") { }
	virtual void VPopulateControls() {
		AddControl( new Graph_CPU( 41, 251, 700, 90 ) );
		AddControl( new Text_CPU_UsagePercent( 297, 16, 90, Colour::TEXT1 ) );
		AddControl( new Text_CPU_Load( 297, 16, 24, Colour::TEXT2 ) );

		AddControl( new Text_CPU_Vendor( 18, 298, 24, Colour::TEXT1 ) );
		AddControl( new Text_CPU_Model( 17, 326, 24, Colour::TEXT1 ) );
		AddControl( new Text_CPU_NumCores( 500, 298, 24, Colour::TEXT1 ) );

		AddControl( new Text_CPU_CoresUsed( 17, 353, 24, Colour::TEXT2 ) );
		AddControl( new Text_CPU_OperatingFreq( 17, 380, 24, Colour::TEXT2 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};