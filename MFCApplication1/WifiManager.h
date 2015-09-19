#pragma once
struct returnresult {
	bool isSuccess;
	CString returnString;
};

class CWifiManager
{
public:
	CWifiManager();
	~CWifiManager();
	bool static setVirtualWLAN(bool isEnabled, CString SSID, CString Password);
	bool static switchWIFI(bool isEnabled);
	bool static modifyWIFIInf(CString SSID, CString Password);
};

