#pragma once

#include "CGraphControl.h"

#include <sigar.h>

class CGraphCPU : public CGraphControl {
public:
	CGraphCPU(int xpos, int ypos, int width, int height );

	virtual void VInit();
	virtual void VDestroy();
	virtual void VDraw();
	virtual float VUpdateGraph();

	sigar_t *m_sigar;
	sigar_cpu_t m_oldcpu;
	int m_currentLoad;
	sf::Font m_font;
};

class CGraphRAM : public CGraphControl {
public:
	CGraphRAM(int xpos, int ypos, int width, int height );

	virtual void VInit();
	virtual void VDestroy();
	virtual void VDraw();
	virtual float VUpdateGraph();

	sigar_t *m_sigar;
	int m_currentRAM;
	sf::Font m_font;
};


//Only inheriting so that we can re-use the periodic update code
class COtherStuff : public CGraphControl {
public:
	COtherStuff(int xpos, int ypos, int width, int height );

	virtual void VInit();
	virtual void VDestroy();
	virtual void VDraw();
	virtual float VUpdateGraph();

	sigar_t *m_sigar;
	float m_gigsFree, m_gigsUsed, m_written, m_read, m_netrx, m_nettx, m_uptime;
	sf::Font m_font;
};