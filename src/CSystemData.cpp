#include "CSystemData.h"
#include "CApp.h"

#include <ctime>
#include <iostream>

extern "C"  {
	#include <sigar_format.h>
}

void CSystemData::Init() {
	sigar_open(&m_sigar);
	m_updateInterval = m_app->Options().GetUpdateInterval();

	// Zero all values
	m_CPU_UsagePercent = 0;
	m_RAM_UsagePercent = 0;
	m_RAM_MegsUsed = 0;
	m_RAM_MegsFree = 0;

	m_HDD_GigsRead = 0;
	m_HDD_GigsWritten = 0;
	m_HDD_GigsUsed = 0;
	m_HDD_GigsFree = 0;
	m_HDD_MegsReadPerSecond = 0;
	m_HDD_MegsWrittenPerSecond = 0;
	m_HDD_PeakRead = 0;
	m_HDD_PeakWrite = 0;
	m_HDD_MRPS_tempDiff = 0;
	m_HDD_MWPS_tempDiff = 0;

	m_NET_MR_diff = 0;
	m_NET_MT_diff = 0;
	m_NET_MegsRx = 0;
	m_NET_MegsTx= 0;
	m_NET_MegsTxPerSecond = 0;
	m_NET_MegsRxPerSecond = 0;

	// SYSTEM STUFF (won't change)
	sigar_sys_info_t sysinfo;
	sigar_sys_info_get( m_sigar, &sysinfo );
	m_OS_Desc = sysinfo.description;
	m_OS_Arch = sysinfo.arch;
	m_OS_BaseVersion = sysinfo.version;
	m_OS_BaseName = sysinfo.name;
	m_OS_Codename = sysinfo.vendor_code_name;
	m_OS_PatchLevel = sysinfo.patch_level;
	m_OS_CPU_Endianness = "little"; //True on all windows anyways
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
	sigar_cpu_info_list_t cpuinfolist;
	sigar_cpu_info_list_get( m_sigar, &cpuinfolist );
	m_CPU_NumCores = cpuinfolist.number;
	m_CPU_Model = cpuinfolist.data->model;
	m_CPU_Vendor = cpuinfolist.data->vendor;
	m_CPU_OperatingFreq = cpuinfolist.data->mhz;

	// RAM USAGE
	sigar_mem_t memt;
	sigar_mem_get(m_sigar, &memt);
	m_RAM_UsagePercent = memt.used_percent;
	m_RAM_MegsUsed = memt.actual_used/1024/1024;
	m_RAM_MegsFree = memt.actual_free/1024/1024;

	// HDD STATS
	sigar_disk_usage_t diskt;
	sigar_disk_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &diskt);
	m_HDD_GigsRead = float(diskt.read_bytes)/1024/1024/1024;
	m_HDD_GigsWritten = float(diskt.write_bytes)/1024/1024/1024;

	if( m_HDD_MRPS_tempDiff != 0 ) {
		m_HDD_MegsReadPerSecond = float(int(((float(diskt.read_bytes)/1024/1024 - m_HDD_MRPS_tempDiff)/m_updateInterval)*10))/10;
		m_HDD_MegsWrittenPerSecond = float(int(((float(diskt.write_bytes)/1024/1024 - m_HDD_MWPS_tempDiff)/m_updateInterval)*10))/10;
	}

	if( m_HDD_MegsReadPerSecond > m_HDD_PeakRead ) m_HDD_PeakRead = m_HDD_MegsReadPerSecond;
	if( m_HDD_MegsWrittenPerSecond > m_HDD_PeakWrite ) m_HDD_PeakWrite = m_HDD_MegsWrittenPerSecond;

	m_HDD_MRPS_tempDiff = float(diskt.read_bytes)/1024/1024;
	m_HDD_MWPS_tempDiff = float(diskt.write_bytes)/1024/1024;

	sigar_file_system_usage_t filet;
	sigar_file_system_usage_get(m_sigar, m_app->Options().GetHDDName().c_str(), &filet);
	m_HDD_GigsFree = float(filet.free*100/1024/1024)/100;
	m_HDD_GigsUsed = float(filet.used*100/1024/1024)/100;

	// NETWORK STATS
	sigar_net_interface_list_t interfaceList; // Get all adapters
	sigar_net_interface_list_get(m_sigar, &interfaceList);
	std::string bestAdapter = "";
	long long bestAmount = -1;
	for( int i = 0; i != interfaceList.number; ++i ) { // Select best adapter
		std::string myName = interfaceList.data[i];
		std::cout << myName << std::endl;
		sigar_net_interface_stat_t myStats;
		sigar_net_interface_stat_get(m_sigar, myName.c_str(), &myStats);
		std::cout << myStats.rx_bytes << std::endl;
		if( long long(myStats.rx_bytes) > bestAmount ) {
			std::cout << "CONDITION!" << std::endl;
			bestAmount = myStats.rx_bytes;
			bestAdapter = myName;
		}
	}
	sigar_net_interface_list_destroy(m_sigar, &interfaceList);

	sigar_net_interface_stat_t bestStats;
	sigar_net_interface_stat_get(m_sigar, bestAdapter.c_str(), &bestStats);
	m_NET_AdapterName = bestAdapter;
	m_NET_MegsRx = float(bestStats.rx_bytes)/1024/1024;
	m_NET_MegsTx = float(bestStats.tx_bytes)/1024/1024;
	
	if( m_NET_MR_diff != 0 ) {
		m_NET_MegsRxPerSecond = float(int(((m_NET_MegsRx - m_NET_MR_diff)/m_updateInterval)*100))/100;
		m_NET_MegsTxPerSecond = float(int(((m_NET_MegsTx - m_NET_MT_diff)/m_updateInterval)*100))/100;
	}

	m_NET_MR_diff = m_NET_MegsRx;
	m_NET_MT_diff = m_NET_MegsTx;

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

std::string CSystemData::CPU_Vendor() {
	return m_CPU_Vendor;
}

std::string CSystemData::CPU_Model() {
	return m_CPU_Model;
}

int CSystemData::CPU_NumCores() {
	return m_CPU_NumCores;
}

float CSystemData::CPU_OperatingFreq() {
	return m_CPU_OperatingFreq;
}

int CSystemData::RAM_UsagePercent() {
	return m_RAM_UsagePercent;
}

int CSystemData::RAM_MegsUsed() {
	return m_RAM_MegsUsed;
}

int CSystemData::RAM_MegsFree() {
	return m_RAM_MegsFree;
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

float CSystemData::HDD_MegsWrittenPerSecond() {
	return m_HDD_MegsWrittenPerSecond;
}

float CSystemData::HDD_MegsReadPerSecond() {
	return m_HDD_MegsReadPerSecond;
}

float CSystemData::HDD_PeakRead() {
	return m_HDD_PeakRead;
}

float CSystemData::HDD_PeakWrite() {
	return m_HDD_PeakWrite;
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