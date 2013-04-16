#pragma once

#include "SharedControls.h"

struct Screen_HDD : public IScreen {
	Screen_HDD() : IScreen("HDD") { }
	virtual void VPopulateControls() {
		
		AddControl( new Text_Custom( 230, 25, 18, Colour::TEXT1, "(Current Transfer Rates)" ) );

		AddControl( new Text_HDD_MegsReadPerSecond( 44, 35, 100, Colour::TEXT1 ) );
		AddControl( new Text_HDD_MegsWrittenPerSecond( 408, 35, 100, Colour::TEXT1 ) );

		AddControl( new Text_Custom( 112, 140, 16, Colour::TEXT2, "MB/Sec Reading" ) );
		AddControl( new Text_Custom( 478, 140, 16, Colour::TEXT2, "MB/Sec Writing" ) );

		AddControl( new Graph_HDDRead( 64, 253, 300, 70 ) );
		AddControl( new Graph_HDDWrite( 432, 253, 300, 70 ) );

		AddControl( new Text_Custom( 54, 287, 22, Colour::TEXT1, "Since Boot:" ) );
		AddControl( new Text_HDD_PeakRead( 54, 322, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_PeakWrite( 54, 351, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_GigsRead( 54, 382, 20, Colour::TEXT2 ) );
		AddControl( new Text_HDD_GigsWritten( 54, 414, 20, Colour::TEXT2 ) );

		AddControl( new Text_HDD_Usage_Title( 472, 330, 23, Colour::TEXT1 ) );
		AddControl( new Text_HDD_Usage( 446, 370, 18, Colour::TEXT2 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};