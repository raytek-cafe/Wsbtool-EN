// wsbTool.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include <atlstr.h>
#include <tlhelp32.h>
#include "easyhook.h"
#include <shellapi.h>
#include <time.h>
#include <string>
#pragma comment(lib,"easyhook32.lib")

//取当前应用程序所在目录
std::wstring GetExePath(void)
{
	wchar_t szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameW(NULL, szFilePath, MAX_PATH);
	(wcsrchr(szFilePath, '\\'))[0] = 0;
	std::wstring path = szFilePath;

	return path;
}
//文件是否存在
bool FileIsExist(std::wstring FilePath) {
	WIN32_FIND_DATA  FindFileData;
	HANDLE hFind;
	hFind = FindFirstFileW(FilePath.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return true;
	}
	return false;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CString dllPath = GetExePath().c_str();
	dllPath += L"\\";
	dllPath += L"MWsbToolLib.dll";
	DWORD nProcessID = 0;


	//创建进程
	STARTUPINFO stStartUpInfo;
	memset(&stStartUpInfo, 0, sizeof(stStartUpInfo));
	stStartUpInfo.cb = sizeof(stStartUpInfo);

	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	std::wstring cmd = GetExePath() + L"\\Windows Style Builder.exe";

	bool ret = ::CreateProcessW(cmd.c_str(),NULL,NULL,NULL,false,CREATE_NEW_CONSOLE,NULL,NULL,&stStartUpInfo,&stProcessInfo);

	if (ret)
	{
		if (!FileIsExist(GetExePath() + L"\\Data\\noLib"))
		{
			NTSTATUS ntStatus = RhInjectLibrary(stProcessInfo.dwProcessId, 0, EASYHOOK_INJECT_DEFAULT, dllPath.GetBuffer(), NULL, NULL, 0);
			if (ntStatus != 0) {
				std::wstring error = L"Oh no, something went wrong! (Extension loading failed code:";
				error += std::to_wstring(ntStatus);
				error += L")";
				MessageBoxW(0, error.c_str(), L"error", MB_ICONERROR);
			}
		}
	}
	else
		MessageBoxW(0, L"Oops, something went wrong! (Application process creation failed)", L"error", MB_ICONERROR);

    return 0;
}