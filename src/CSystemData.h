#pragma once

#include <SFML\System.hpp>
#include <sigar.h>

class CApp;

class CSystemData {
public:
	void Init();
	void Step();
	void Destroy();

	int CPU_UsagePercent();
	int RAM_UsagePercent();

	float HDD_GigsWritten();
	float HDD_GigsRead();
	float HDD_GigsUsed();
	float HDD_GigsFree();
	float HDD_MegsWrittenPerSecond();
	float HDD_MegsReadPerSecond();
	float HDD_PeakRead();
	float HDD_PeakWrite();

	std::string UserName();
	float Uptime();
	std::string TimeString();

	friend class CApp;

private:
	void RetrieveAllData();

	CApp *m_app;

	sigar_t *m_sigar;

	float m_updateInterval;
	sf::Clock m_updateClock;

	sf::Clock m_perSecondClock;

// Real data begins here

	//CPU USAGE
	sigar_cpu_t m_oldcpu;
	int m_CPU_UsagePercent;

	//RAM USAGE
	int m_RAM_UsagePercent;

	//HDD STATS
	float m_HDD_GigsWritten;
	float m_HDD_GigsRead;
	float m_HDD_GigsFree;
	float m_HDD_GigsUsed;
	float m_HDD_MegsReadPerSecond;
	float m_HDD_MegsWrittenPerSecond;
	float m_HDD_PeakRead;
	float m_HDD_PeakWrite;
	float m_HDD_MRPS_tempDiff;
	float m_HDD_MWPS_tempDiff;

	//USER STATS
	std::string m_userName;
	float m_uptime;

	//TIME
	std::string m_timeString;
};