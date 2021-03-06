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
	std::string CPU_Vendor();
	std::string CPU_Model();
	int CPU_NumCores();
	float CPU_OperatingFreq();

	int RAM_UsagePercent();
	int RAM_MegsUsed();
	int RAM_MegsFree();

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
	std::string m_CPU_Vendor;
	std::string m_CPU_Model;
	int m_CPU_NumCores;
	float m_CPU_OperatingFreq;

	//RAM USAGE
	int m_RAM_UsagePercent;
	int m_RAM_MegsUsed;
	int m_RAM_MegsFree;

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

public: // To lazy for getters here
	//SYSTEM STUFF
	std::string m_OS_Desc;
	std::string m_OS_Arch;
	std::string m_OS_BaseVersion;
	std::string m_OS_BaseName;
	std::string m_OS_Codename;
	std::string m_OS_PatchLevel;
	std::string m_OS_CPU_Endianness;

	//NET
	std::string m_NET_AdapterName;
	float m_NET_MegsTx;
	float m_NET_MegsRx;
	float m_NET_MegsTxPerSecond;
	float m_NET_MegsRxPerSecond;
	float m_NET_MR_diff;
	float m_NET_MT_diff;
};