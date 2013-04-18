#pragma once

#include "CGraphControl.h"
#include "CTextControl.h"

struct Graph_CPU : public CGraphControl {
	Graph_CPU(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return m_app->SystemData().CPU_UsagePercent(); }
};

struct Graph_RAM : public CGraphControl {
	Graph_RAM(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return m_app->SystemData().RAM_UsagePercent(); }
};

struct Graph_NET : public CGraphControl {
	Graph_NET(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return (m_app->SystemData().m_NET_MegsRxPerSecond + m_app->SystemData().m_NET_MegsTxPerSecond)/m_app->Options().GetMaxNetTransfer()*100; }
};

struct Graph_HDDRead : public CGraphControl {
	Graph_HDDRead(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return (m_app->SystemData().HDD_MegsReadPerSecond()/m_app->Options().GetMaxHDDTransfer())*100; }
};

struct Graph_HDDWrite : public CGraphControl {
	Graph_HDDWrite(int xpos, int ypos, int width, int height ): CGraphControl(xpos, ypos, width, height, 50, 100 ) {}
	virtual float VUpdateGraph() { return (m_app->SystemData().HDD_MegsWrittenPerSecond()/m_app->Options().GetMaxHDDTransfer())*100; }
};

struct Text_CPU_UsagePercent : public CTextControl {
	Text_CPU_UsagePercent( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().CPU_UsagePercent() << "%"; }
};

struct Text_CPU_Load : public CTextControl {
	Text_CPU_Load( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "CPU Load"; }
};

struct Text_CPU_Model : public CTextControl {
	Text_CPU_Model( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "CPU Model: " << m_app->SystemData().CPU_Model(); }
};

struct Text_CPU_Vendor : public CTextControl {
	Text_CPU_Vendor( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "CPU Vendor: " << m_app->SystemData().CPU_Vendor(); }
};

struct Text_CPU_NumCores : public CTextControl {
	Text_CPU_NumCores( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Number of cores: " << m_app->SystemData().CPU_NumCores(); }
};

struct Text_CPU_CoresUsed : public CTextControl {
	Text_CPU_CoresUsed( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Estimated " << float(int((float(m_app->SystemData().CPU_UsagePercent())/100)*float(m_app->SystemData().CPU_NumCores())*10))/10 << " cores in use"; }
};

struct Text_CPU_OperatingFreq : public CTextControl {
	Text_CPU_OperatingFreq( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Operating frequency: " << m_app->SystemData().CPU_OperatingFreq() << "MHz"; }
};

struct Text_RAM_Rotated : public CTextControl {
	Text_RAM_Rotated( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { m_text.setRotation(-90); }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "RAM"; }
};

struct Text_RAM_UsagePercent_Rotated : public CTextControl {
	Text_RAM_UsagePercent_Rotated( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { m_text.setRotation(-90); }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_UsagePercent() << "%"; }
};

struct Text_RAM_UsagePercent : public CTextControl {
	Text_RAM_UsagePercent( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_UsagePercent() << "%"; }
};

struct Text_RAM_MegsUsed : public CTextControl {
	Text_RAM_MegsUsed( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_MegsUsed() << "MB in use"; }
};

struct Text_RAM_MegsFree : public CTextControl {
	Text_RAM_MegsFree( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_MegsFree() << "MB available"; }
};

struct Text_RAM_Total : public CTextControl {
	Text_RAM_Total( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().RAM_MegsUsed() + m_app->SystemData().RAM_MegsFree() << "MB physical memory"; }
};

struct Text_HDD_Usage_Title : public CTextControl {
	Text_HDD_Usage_Title( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "HDD Usage: (" << m_app->Options().GetHDDName() << ")"; }
};

struct Text_HDD_GigsWritten : public CTextControl {
	Text_HDD_GigsWritten( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsWritten() << "Gb Written"; }
};

struct Text_HDD_GigsRead : public CTextControl {
	Text_HDD_GigsRead( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsRead() << "Gb Read"; }
};

struct Text_HDD_MegsWrittenPerSecond : public CTextControl {
	Text_HDD_MegsWrittenPerSecond( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_MegsWrittenPerSecond(); }
};

struct Text_HDD_MegsReadPerSecond : public CTextControl {
	Text_HDD_MegsReadPerSecond( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_MegsReadPerSecond(); }
};

struct Text_HDD_PeakRead : public CTextControl {
	Text_HDD_PeakRead( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Peak read: " << m_app->SystemData().HDD_PeakRead() << "MB/Sec"; }
};

struct Text_HDD_PeakWrite : public CTextControl {
	Text_HDD_PeakWrite( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Peak write: " << m_app->SystemData().HDD_PeakWrite() << "MB/Sec"; }
};

struct Text_HDD_Usage : public CTextControl {
	Text_HDD_Usage( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().HDD_GigsFree() << "Gb free of " << 
		m_app->SystemData().HDD_GigsFree() + m_app->SystemData().HDD_GigsUsed() << "Gb"; }
};

struct Text_NET_AdapterName : public CTextControl {
	Text_NET_AdapterName( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Using adapter [" << m_app->SystemData().m_NET_AdapterName << "]"; }
};

struct Text_NET_MegsTx : public CTextControl {
	Text_NET_MegsTx( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().m_NET_MegsTx << "MB Transmitted"; }
};

struct Text_NET_MegsRx : public CTextControl {
	Text_NET_MegsRx( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().m_NET_MegsRx << "MB Recieved"; }
};

struct Text_NET_MegsRxPerSecond : public CTextControl {
	Text_NET_MegsRxPerSecond( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().m_NET_MegsRxPerSecond << "MB/Sec Down"; }
};

struct Text_NET_MegsTxPerSecond : public CTextControl {
	Text_NET_MegsTxPerSecond( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().m_NET_MegsTxPerSecond << "MB/Sec Up"; }
};

struct Text_NET_BandwidthOfGraph : public CTextControl {
	Text_NET_BandwidthOfGraph( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Combined bandwidth usage (% of " << m_app->Options().GetMaxNetTransfer() << "MB/Sec):"; }
};

struct Text_UserName : public CTextControl {
	Text_UserName( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "User: " << m_app->SystemData().UserName(); }
};

struct Text_Uptime : public CTextControl {
	Text_Uptime( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "Uptime: " << m_app->SystemData().Uptime() << "Hr"; }
};

struct Text_Chrono : public CTextControl {
	Text_Chrono( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << m_app->SystemData().TimeString(); }
};

struct Text_SebLogo : public CTextControl {
	Text_SebLogo( int x, int y, int sz, Colour::Type col ) : CTextControl(x, y, sz, col) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << "sebholzapfel.com"; }
};

struct Text_Custom : public CTextControl {
	Text_Custom( int x, int y, int sz, Colour::Type col, std::string text ) : CTextControl(x, y, sz, col), txt(text) { }
	virtual void VUpdateText( std::ostringstream &oss ) { oss << txt; }
	std::string txt;
};