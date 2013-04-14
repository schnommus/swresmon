#include "CSystemData.h"
#include "CApp.h"

#include <ctime>

extern "C"  {
	#include <sigar_format.h>
}

void CSystemData::Init() {
	sigar_open(&m_sigar);
	m_updateInterval = m_app->Options().GetUpdateInterval();

	// Zero all values
	m_CPU_UsagePercent = 0;
	m_RAM_UsagePercent = 0;
	m_HDD_GigsRead = 0;
	m_HDD_GigsWritten = 0;
	m_HDD_GigsUsed = 0;
	m_HDD_GigsFree = 0;
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

	// HDD STATS
	sigar_disk_usage_t diskt;
	sigar_disk_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &diskt);
	m_HDD_GigsRead = float(diskt.read_bytes)/1024/1024/1024;
	m_HDD_GigsWritten = float(diskt.write_bytes)/1024/1024/1024;

	sigar_file_system_usage_t filet;
	sigar_file_system_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &filet);
	m_HDD_GigsFree = float(filet.free*100/1024/1024)/100;
	m_HDD_GigsUsed = float(filet.used*100/1024/1024)/100;

	// USER STATS
	char buf[32];
	DWORD sbuf = 31;
	GetUserName(buf, &sbuf);
	m_userName = buf;

	sigar_uptime_t upt;
	sigar_uptime_get(m_sigar, &upt);
	m_uptime = float(int(upt.uptime)/36)/100;

	// TIME
	time_t ct = time(0);
	m_timeString = ctime(&ct);
}

int CSystemData::CPU_UsagePercent() {
	return m_CPU_UsagePercent;
}

int CSystemData::RAM_UsagePercent() {
	return m_RAM_UsagePercent;
}

float CSystemData::HDD_GigsWritten() {
	return m_HDD_GigsWritten;
}
	
float CSystemData::HDD_GigsRead() {
	return m_HDD_GigsRead;
}

float CSystemData::HDD_GigsUsed() {
	return m_HDD_GigsUsed;
}

float CSystemData::HDD_GigsFree() {
	return m_HDD_GigsFree;
}

std::string CSystemData::UserName() {
	return m_userName;
}

float CSystemData::Uptime() {
	return m_uptime;
}

std::string CSystemData::TimeString() {
	return m_timeString;
}