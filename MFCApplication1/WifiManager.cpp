#include "stdafx.h"
#include "WifiManager.h"


CWifiManager::CWifiManager()
{
}


CWifiManager::~CWifiManager()
{
}

bool CWifiManager::setVirtualWLAN(bool isEnabled, CString SSID, CString Password) {
	returnresult returnValue;
	if (!isEnabled) { // ½ûÓÃÐéÄâÍø¿¨
		ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("netsh wlan set hostednetwork mode = disallow"), NULL, SW_HIDE);
		return true;
	} 
	CString command;
	command.Format(_T("/c netsh wlan set hostednetwork mode = allow ssid = %s key = %s"), SSID, Password);
	//system("netsh wlan set hostednetwork mode = allow ssid = WLAN key = WLAN1234");
	//system("netsh wlan start hostednetwork");
	ShellExecute(NULL, _T("open"), _T("cmd.exe"), command, NULL, SW_HIDE);
	ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/c netsh wlan start hostednetwork"), NULL, SW_HIDE);
	//returnValue.isSuccess = true;
	//return returnValue;
	return true;
}

bool CWifiManager::switchWIFI(bool isEnabled) {
	switch (isEnabled)
	{
	case true:
		ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/c netsh wlan start hostednetwork"), NULL, SW_HIDE);
		break;
	default:
		ShellExecute(NULL, _T("open"), _T("cmd.exe"), _T("/c netsh wlan stop hostednetwork"), NULL, SW_HIDE);
		break;
	}
	return true;
}

bool CWifiManager::modifyWIFIInf(CString SSID, CString Password) {
	CString command;
	command.Format(_T("/c netsh wlan set hostednetwork ssid = %s key = %s"), SSID, Password);
	return true;
}
