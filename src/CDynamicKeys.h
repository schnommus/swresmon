#pragma once

#include "CVirtualRenderSurface.h"

class CApp;

class CDynamicKeys {
public:
	CDynamicKeys();
	void Init();
	void Step();
	void Draw();
	sf::Texture GetAsTexture();
	void SendToDevice();

	friend class CApp;
private:
	void DrawKeyGrid();
	void DrawIcons();

	CApp *m_app;
	sf::Font m_keyFont;
	sf::Vector2i m_keySize;
	CVirtualRenderSurface m_virtualRenderSurface;

	sf::Texture m_selectionImage;
	sf::Texture m_keyIcons[10];
};