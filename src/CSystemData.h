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

private:
	void RetrieveAllData();

	CApp *m_app;

	sigar_t *m_sigar;

	float m_updateInterval;
	sf::Clock m_updateClock;

// Real data begins here

	//CPU USAGE
	sigar_cpu_t m_oldcpu;
	int m_CPU_UsagePercent;

	//RAM USAGE
	int m_RAM_UsagePercent;
};