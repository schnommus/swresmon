#include "CSystemData.h"
#include "CApp.h"

extern "C"  {
	#include <sigar_format.h>
}

void CSystemData::Init() {
	sigar_open(&m_sigar);
	m_updateInterval = m_app->Options().GetUpdateInterval();
}

void CSystemData::Step() {
	if(m_updateClock.getElapsedTime().asSeconds() > m_updateInterval ) {
		RetrieveAllData();
		m_updateClock.restart();
	}
}

void CSystemData::Destroy() {
	sigar_close(m_sigar);
}

void CSystemData::RetrieveAllData() {
	// CPU USAGE
	sigar_cpu_t cpu;
	sigar_cpu_get( m_sigar, &cpu );
	sigar_cpu_perc_t perc;
	sigar_cpu_perc_calculate(&m_oldcpu, &cpu, &perc);
	m_oldcpu = cpu;
	m_CPU_UsagePercent = perc.combined*100;

	// RAM USAGE
	sigar_mem_t memt;
	sigar_mem_get(m_sigar, &memt);
	m_RAM_UsagePercent = memt.used_percent;
}

int CSystemData::CPU_UsagePercent() {
	return m_CPU_UsagePercent;
}

int CSystemData::RAM_UsagePercent() {
	return m_RAM_UsagePercent;
}