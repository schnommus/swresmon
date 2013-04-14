#include "CSystemGraphs.h"
#include <iostream>
#include <sstream>
#include <ctime>

extern "C"  {
	#include <sigar_format.h>
}

CGraphCPU::CGraphCPU(int xpos, int ypos, int width, int height ) :
	CGraphControl(xpos, ypos, width, height, 50, 100 ) { }

float CGraphCPU::VUpdateGraph() {
	return m_app->SystemData().CPU_UsagePercent();
}

/*void CGraphCPU::VDraw() {
	CGraphControl::VDraw();

	// Draw the numbers
	std::ostringstream iss; iss << m_currentLoad << "%";
	sf::Text t( iss.str(), m_font, 90 );
	t.setColor( m_app->Options().GetColourOf(Colour::TEXT1) );
	t.setPosition(65, 10);

	// Draw "CPU Load"
	std::ostringstream iss2; iss2 << "CPU Load";
	sf::Text t2( iss2.str(), m_font, 24 );
	t2.setColor( m_app->Options().GetColourOf(Colour::TEXT2) );
	t2.setPosition(220, 110);

	m_app->RenderSurface().draw(t);
	m_app->RenderSurface().draw(t2);
}*/



CGraphRAM::CGraphRAM(int xpos, int ypos, int width, int height ) :
CGraphControl(xpos, ypos, width, height, 50, 100 ) { }


void CGraphRAM::VInit() {
	m_currentRAM = 0;
	CGraphControl::VInit();

	m_font.loadFromFile( m_app->Options().GetFontFilename() );

	sigar_open(&m_sigar);
}

float CGraphRAM::VUpdateGraph() {
	sigar_mem_t memt;
	sigar_mem_get(m_sigar, &memt);
	m_currentRAM = memt.used_percent;
	return m_currentRAM;
}

void CGraphRAM::VDestroy() {
	CGraphControl::VDestroy();
	sigar_close(m_sigar);
}

void CGraphRAM::VDraw() {
	CGraphControl::VDraw();

	std::ostringstream iss2; iss2 << "RAM";
	sf::Text t2( iss2.str(), m_font, 24 );
	t2.rotate(-90);
	t2.setPosition(733, 112);
	t2.setColor( m_app->Options().GetColourOf(Colour::TEXT1) );

	std::ostringstream iss; iss << m_currentRAM << "%";
	sf::Text t(iss.str(), m_font, 18 );
	t.rotate(-90);
	t.setPosition(763, 97);
	t.setColor( m_app->Options().GetColourOf(Colour::TEXT2) );

	m_app->RenderSurface().draw(t);
	m_app->RenderSurface().draw(t2);
}


// Hacky, but only inheriting to re-use the periodic update code
// TODO: Move into a specialized text-handling class
COtherStuff::COtherStuff(int xpos, int ypos, int width, int height ) :
CGraphControl(xpos, ypos, width, height, 50, 100 ) { }

void COtherStuff::VInit() {
	CGraphControl::VInit();

	m_font.loadFromFile( m_app->Options().GetFontFilename() );

	sigar_open(&m_sigar);
}

float COtherStuff::VUpdateGraph() {
	sigar_disk_usage_t diskt;
	sigar_disk_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &diskt);
	m_read = diskt.read_bytes;
	m_written = diskt.write_bytes;

	sigar_file_system_usage_t filet;
	sigar_file_system_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &filet);
	m_gigsFree = float(filet.free)/1024/1024;
	m_gigsUsed = float(filet.used)/1024/1024;

	/*sigar_net_interface_config_t netct; // Tried network stuff, was reading zeros so nope
	sigar_net_interface_config_primary_get(m_sigar, &netct);
	sigar_net_interface_stat_t netst;
	sigar_net_interface_stat_get(m_sigar, netct.type, &netst);
	m_netrx = netst.rx_packets/1e16;
	m_nettx = netst.tx_packets;*/

	sigar_uptime_t upt;
	sigar_uptime_get(m_sigar, &upt);
	m_uptime = (upt.uptime)/3600;
	return 0;
}

void COtherStuff::VDestroy() {
	CGraphControl::VDestroy();
	sigar_close(m_sigar);
}

void COtherStuff::VDraw() {
	// Don't actually draw the graph
	//CGraphControl::VDraw();

	// Shorten the names of text colours - using them a lot below!
	sf::Color text1_col = m_app->Options().GetColourOf(Colour::TEXT1),
			  text2_col = m_app->Options().GetColourOf(Colour::TEXT2);


	// Draw a bunch of textual stats

	std::ostringstream iss; iss << "HDD Usage: (" << m_app->Options().GetHDDName() << ")";
	sf::Text t(iss.str(), m_font, 26 );
	t.setPosition(470, 157);
	t.setColor(text1_col);
	m_app->RenderSurface().draw(t);

	iss.str(""); iss << float(m_read)/1024/1024/1024 << "Gb Read";
	t.setString(iss.str());
	t.setCharacterSize(20);
	t.setPosition(473, 194);
	t.setColor(text2_col);
	m_app->RenderSurface().draw(t);

	iss.str(""); iss << float(m_written)/1024/1024/1024 << "Gb Written";
	t.setString(iss.str());
	t.setCharacterSize(20);
	t.setPosition(473, 222 );
	t.setColor(text2_col);
	m_app->RenderSurface().draw(t);

	iss.str(""); iss << float(int(m_gigsFree*100))/100 << "Gb free of " << float(int((m_gigsUsed+m_gigsFree)*100))/100 << "Gb";
	t.setString(iss.str());
	t.setCharacterSize(16);
	t.setPosition(473, 253 );
	t.setColor(text2_col);
	m_app->RenderSurface().draw(t);

	char buf[32];
	DWORD sbuf = 31;
	GetUserName(buf, &sbuf);
	iss.str(""); iss << "User: " << buf;
	t.setString(iss.str());
	t.setCharacterSize(22);
	t.setPosition(473, 323 );
	t.setColor(text1_col);
	m_app->RenderSurface().draw(t);

	iss.str(""); iss << "Uptime: " << float(int(m_uptime*100))/100 << "Hr";
	t.setString(iss.str());
	t.setCharacterSize(22);
	t.setPosition(473, 353 );
	t.setColor(text1_col);
	m_app->RenderSurface().draw(t);

	time_t ct = time(0);
	iss.str(""); iss << "Chrono: " << ctime(&ct);
	t.setString(iss.str());
	t.setCharacterSize(12);
	t.setPosition(473, 445 );
	t.setColor(text1_col);
	m_app->RenderSurface().draw(t);

	iss.str(""); iss << "sebholzapfel.com";
	t.setString(iss.str());
	t.setCharacterSize(8);
	t.setPosition(10, 470 );
	t.setColor(sf::Color(255, 255, 255, 50));
	if( m_app->Options().ShowLink() ) m_app->RenderSurface().draw(t);
}