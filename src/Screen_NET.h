#pragma once

#include "SharedControls.h"

struct Screen_NET : public IScreen {
	Screen_NET() : IScreen("NET") { }
	virtual void VPopulateControls() {
		AddControl( new Text_NET_AdapterName( 266, 16, 22, Colour::TEXT1 ) );

		AddControl( new Text_NET_BandwidthOfGraph( 87, 78, 22, Colour::TEXT1 ) );
		AddControl( new Graph_NET(45, 299, 700, 160 ) );

		AddControl( new Text_Custom( 57, 327, 24, Colour::TEXT1, "Since Boot:" ) );
		AddControl( new Text_NET_MegsRx( 57, 359, 22, Colour::TEXT2 ) );
		AddControl( new Text_NET_MegsTx( 57, 389, 22, Colour::TEXT2 ) );

		AddControl( new Text_Custom( 485, 327, 24, Colour::TEXT1, "Bandwidth usage:" ) );
		AddControl( new Text_NET_MegsRxPerSecond( 485, 359, 22, Colour::TEXT2 ) );
		AddControl( new Text_NET_MegsTxPerSecond( 485, 389, 22, Colour::TEXT2 ) );

		if( m_app->Options().ShowLink() )
			AddControl( new Text_SebLogo( 10, 470, 8, Colour::TEXT2 ) );
	}
};