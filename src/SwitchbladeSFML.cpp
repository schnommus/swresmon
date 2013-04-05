#include <iostream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SFML/Graphics.hpp>
#include <SwitchBlade.h>

unsigned short outData[800*480];
sf::Image bufImage;

void ConvertColourProfile() {
	const sf::Uint8 *im = bufImage.getPixelsPtr();
	for( long i = 0; i != 800*480; ++i ) {
		int xpos = i%800;
		int ypos = i/800;
		outData[i] = 0x1F & im[800*ypos*4+xpos*4+1]>>3;
		outData[i] |= 0x7E0 & im[800*ypos*4+xpos*4+2]<<3;
		outData[i] |= 0xF800 & im[800*ypos*4+xpos*4]<<8;

	}
	outData[800*4+40] = 0xFFFF;
}

int WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, char*, int nShowCmd ) {
	std::cout << "Starting SFML..." << std::endl;

	//sf::RenderWindow window( sf::VideoMode(800, 480), "SFML Switchblade Hook" );

	sf::RenderTexture rendertex;
	rendertex.create(800, 480);

	sf::Texture tex; tex.loadFromFile("images.jpg");
	sf::Sprite sprite(tex);
	sprite.setOrigin(tex.getSize().x/2, tex.getSize().y/2);
	sprite.setPosition( rendertex.getSize().x/2, rendertex.getSize().y/2 );

	std::cout << "Hooking to Switchblade..." << std::endl;
	RzSBStart();

	sf::Clock frameClock;
	double frameTime = 0.0;
	while( true /*window.isOpen()*/ ) {
		/*sf::Event e;
		while( window.pollEvent(e) ) {
			if (e.type == sf::Event::Closed)
				window.close();
		}*/

		//logic
		sprite.rotate(100*frameTime);

		//window.clear();

		rendertex.clear();

		//draw stuff
		rendertex.draw(sprite);

		//draw framerate
		std::ostringstream iss; iss << int(1/frameTime) << " FPS";
		sf::Text t( iss.str(), sf::Font::getDefaultFont(), 20 );
		rendertex.draw(t);

		rendertex.display();

		bufImage = rendertex.getTexture().copyToImage();

		//wchar_t *pt = L"screenshot.png";
		//RzSBSetImageTouchpad(pt);
		
		ConvertColourProfile();
		RZSBSDK_BUFFERPARAMS params;
		params.PixelType = RGB565;
		params.DataSize = 800*480*2;
		params.pData = reinterpret_cast<unsigned char*>(outData);
		RzSBRenderBuffer(RZSBSDK_DISPLAY_WIDGET, &params );

		//window.draw(sf::Sprite(rendertex.getTexture()));

		//window.display();

		frameTime = frameClock.getElapsedTime().asSeconds();
		frameClock.restart();
	}

	RzSBStop();

	return 0;
}