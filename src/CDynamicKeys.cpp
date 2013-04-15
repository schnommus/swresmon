#include "CDynamicKeys.h"
#include "CApp.h"

#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SwitchBlade.h>

CDynamicKeys::CDynamicKeys() : 
	m_keySize(115, 115) { }

CApp *globalApp;

HRESULT STDMETHODCALLTYPE MyDynamicKeyCallback(RZSBSDK_DKTYPE dk, RZSBSDK_KEYSTATETYPE dkState) {
	HRESULT hReturn = S_OK;
	// If it is dynamic key 1 and the key is in the down state
	if(dk == RZSBSDK_DK_6 && dkState == RZSBSDK_KEYSTATE_DOWN)
		globalApp->SetActiveScreen("CLASSIC");
	if(dk == RZSBSDK_DK_7 && dkState == RZSBSDK_KEYSTATE_DOWN)
		globalApp->SetActiveScreen("CLOCK");
	return hReturn;
}

typedef HRESULT (STDMETHODCALLTYPE DKEvent)(RZSBSDK_DKTYPE, RZSBSDK_KEYSTATETYPE);

void CDynamicKeys::Init() {
	// Will have enough space for all 10 keys
	m_virtualRenderSurface.Init( m_keySize.x*5, m_keySize.y*2 );
	globalApp = m_app;

#ifndef EMULATE_SCREEN
	RzSBDynamicKeySetCallback(reinterpret_cast<DKEvent*>(MyDynamicKeyCallback));
#endif
}

void CDynamicKeys::Step() {
#ifdef EMULATE_SCREEN
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_6, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_7, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num3 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_8, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num4 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_9, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num5 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_10, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num6 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_1, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num7 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_2, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num8 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_3, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num9 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_4, RZSBSDK_KEYSTATE_DOWN );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num0 ) )
		MyDynamicKeyCallback( RZSBSDK_DK_5, RZSBSDK_KEYSTATE_DOWN );
#endif
}

void CDynamicKeys::Draw() {
	m_virtualRenderSurface.RenderSurface().clear();

	// Actual drawing goes here
	for( int i = 0; i != m_app->m_screens.size(); ++i ) {
		sf::Text t(m_app->m_screens[i]->m_name.c_str(), sf::Font::getDefaultFont(), 20);
		t.setColor( m_app->Options().GetColourOf( Colour::TEXT2 ) );
		if( m_app->m_activeScreenName == m_app->m_screens[i]->m_name ) {
			t.setColor( m_app->Options().GetColourOf( Colour::TEXT1 ) );
		}
		t.setPosition(i*115+5, 73);
		t.rotate(-45);
		m_virtualRenderSurface.RenderSurface().draw(t);
	}

#ifdef EMULATE_SCREEN
	DrawKeyGrid();
#endif

	m_virtualRenderSurface.RenderSurface().display();
}

void CDynamicKeys::DrawKeyGrid() {
	for( int i = 0; i != m_keySize.x*5; i += m_keySize.x ) {
		for( int j = 0; j != m_keySize.y*2; j += m_keySize.y ) {
			sf::RectangleShape r(sf::Vector2f(115, 115));
			r.setFillColor( sf::Color(0, 0, 0, 0) );
			r.setOutlineColor( sf::Color( 255, 255, 255, 120 ) );
			r.setOutlineThickness( 1 );
			r.setPosition(i, j);
			m_virtualRenderSurface.RenderSurface().draw(r);
		}
	}
}

void CDynamicKeys::SendToDevice() {
#ifndef EMULATE_SCREEN
	// Tried using RenderBuffer, but API didn't like me for some reason. Now using files.
	/*const sf::Vector2u sz( m_keySize.x, m_keySize.y );

	// Set up buffer parameters
	RZSBSDK_BUFFERPARAMS params;
	params.PixelType = RGB565;
	params.DataSize = sz.x*sz.y*2;
	params.pData = reinterpret_cast<unsigned char*>( m_virtualRenderSurface.GetSubsectionRGB565( m_keySize.x*2, 0, m_keySize.x, m_keySize.y ) );

	// Then do the actual sending
	RzSBRenderBuffer(RZSBSDK_DISPLAY_DK_3, &params );*/
	m_virtualRenderSurface.GetSubsectionAsImage(0, 115, 115, 115).saveToFile("DynamicKeyImages/DK1.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115, 115, 115, 115).saveToFile("DynamicKeyImages/DK2.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*2, 115, 115, 115).saveToFile("DynamicKeyImages/DK3.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*3, 115, 115, 115).saveToFile("DynamicKeyImages/DK4.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*4, 115, 115, 115).saveToFile("DynamicKeyImages/DK5.png");
	m_virtualRenderSurface.GetSubsectionAsImage(0, 0, 115, 115).saveToFile("DynamicKeyImages/DK6.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115, 0, 115, 115).saveToFile("DynamicKeyImages/DK7.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*2, 0, 115, 115).saveToFile("DynamicKeyImages/DK8.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*3, 0, 115, 115).saveToFile("DynamicKeyImages/DK9.png");
	m_virtualRenderSurface.GetSubsectionAsImage(115*4, 0, 115, 115).saveToFile("DynamicKeyImages/DK10.png");

	RzSBSetImageDynamicKey( RZSBSDK_DK_1, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK1.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_2, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK2.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_3, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK3.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_4, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK4.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_5, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK5.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_6, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK6.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_7, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK7.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_8, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK8.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_9, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK9.png" );
	RzSBSetImageDynamicKey( RZSBSDK_DK_10, RZSBSDK_KEYSTATE_UP, L"DynamicKeyImages/DK10.png" );
#endif
}

sf::Texture CDynamicKeys::GetAsTexture() {
	return m_virtualRenderSurface.RenderSurface().getTexture();
}