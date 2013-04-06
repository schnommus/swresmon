#include <iostream>

#include "CApp.h"
#include "CSystemGraphs.h"

class ImageControl : public IControl {
public:
	virtual void VInit() {
		m_texture.loadFromFile("images.jpg");
		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin( m_texture.getSize().x/2, m_texture.getSize().y/2 );
		m_sprite.setPosition( m_app->RenderSurface().getSize().x/2, m_app->RenderSurface().getSize().y/2 );
	}

	virtual void VStep() {
		m_sprite.rotate(100*m_app->GetFrameTime());
	}

	virtual void VDraw() {
		m_app->RenderSurface().draw(m_sprite);
	}

	virtual void VDestroy() {

	}

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


// Treat as windows app to avoid console displaying
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {

	CApp app;

	app.Initialize(800, 480);

	app.AddControl(new CGraphCPU( 17, 450, 400, 270 ) );
	app.AddControl(new CGraphRAM( 445, 120, 280, 90 ) );
	/*app.AddControl(new CGraphRAM( 465, 280, 260, 90 ) );
	app.AddControl(new CGraphRAM( 465, 440, 260, 90 ) );*/
	app.AddControl(new COtherStuff(2000, 2000, 1, 1));


	app.Run();

	return 0;
}