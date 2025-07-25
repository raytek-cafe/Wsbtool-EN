// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <string>
#include <vector>
#include "easyhook.h"
#include <thread>
#include <shellapi.h>
#include <tlhelp32.h>
#pragma comment(lib, "EasyHook32.lib")


extern LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern void AddHook(HMODULE Module);

std::vector<HWND>hwndList;

//取当前应用程序所在目录
std::wstring GetExePath(void)
{
	wchar_t szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameW(NULL, szFilePath, MAX_PATH);
	(wcsrchr(szFilePath, '\\'))[0] = 0;
	std::wstring path = szFilePath;

	return path;
}

//读注册表字符串
std::wstring GetRegSZ(HKEY hKey, LPCWSTR SubKey, LPCWSTR KeyName) {

	HKEY tkey;

	if (ERROR_SUCCESS == RegOpenKeyExW(hKey, SubKey, 0, KEY_READ, &tkey))
	{
		wchar_t dwValue[256];
		DWORD dwSzType = REG_SZ;
		DWORD dwSize = sizeof(dwValue);
		if (RegQueryValueExW(tkey, KeyName, 0, &dwSzType, (LPBYTE)& dwValue, &dwSize) != ERROR_SUCCESS)
		{
			return L"Query Error";
		}
		return dwValue;
	}
	RegCloseKey(tkey);
	return L"Open Error";
}

struct XSleep_Structure
{
	int duration;
	HANDLE eventHandle;
};

extern DWORD WINAPI XSleepThread(LPVOID pWaitTime)
{
	XSleep_Structure* sleep = (XSleep_Structure*)pWaitTime;

	Sleep(sleep->duration);
	SetEvent(sleep->eventHandle);

	return 0;
}

//不阻塞延迟
void Sleep_(int times) {
	XSleep_Structure sleep;
	sleep.duration = times;
	sleep.eventHandle = CreateEvent(NULL, TRUE, FALSE, NULL);

	DWORD threadId;
	CreateThread(NULL, 0, &XSleepThread, &sleep, 0, &threadId);
	MSG msg;
	while (::WaitForSingleObject(sleep.eventHandle, 0) == WAIT_TIMEOUT)
	{
		//获取和发送消息
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	CloseHandle(sleep.eventHandle);
}

//枚举窗口
typedef struct EnumHWndsArg
{
	std::vector<HWND>* vecHwndList;
	DWORD dwProcessId;
}EnumHWndsArg, * LPEnumHWndsArg;

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	EnumHWndsArg* pArg = (LPEnumHWndsArg)lParam;
	DWORD  processId;
	GetWindowThreadProcessId(hwnd, &processId);
	if (processId == pArg->dwProcessId)
	{
		pArg->vecHwndList->push_back(hwnd);
	}
	return TRUE;
}

//枚举子窗口
std::string text;
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM pParam) {
	HWND phWnd = (HWND)pParam;
	if (NULL == hwnd) { return FALSE; }

	if (::IsWindow(hwnd))
	{
		char temp[300];
		GetWindowTextA(hwnd, temp, 301);
		std::string title = temp;
		text += "\n" + title;
	}
	return TRUE;
}

//取指定窗口下所有子窗口
void GetHWndsByProcessID(std::vector<HWND>& vecHWnds)
{
	EnumHWndsArg wi;
	wi.dwProcessId = GetCurrentProcessId();
	wi.vecHwndList = &vecHWnds;
	EnumWindows(lpEnumFunc, (LPARAM)& wi);
}

// 枚举窗口进程ID是否为主进程
HWND g_hwnd;
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	DWORD ProcessId;
	GetWindowThreadProcessId(hWnd, &ProcessId);

	if (IsWindowVisible(hWnd) && ProcessId == (DWORD)lParam) {
		g_hwnd = hWnd;
	}
	return TRUE;
}

//查找主窗口句柄
extern void GetMainHwnd()
{
	DWORD dwCurrentProcessId = GetCurrentProcessId();

	//等待窗口载入
Enumwindow:	while (g_hwnd == NULL)
{
	EnumWindows(EnumWindowsProc, (LPARAM)dwCurrentProcessId);
};
			//等待激活后主窗口载入
			char temp[300];
			GetWindowTextA(g_hwnd, temp, 301);
			std::string title = temp;
			if (title == "Activate Windows Style Builder")
			{
				Sleep_(2000);
				g_hwnd = NULL;
				goto Enumwindow;
			}
}

HMODULE g_Module;
UINT G_HOOK;
long lpPrevWndProc;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		g_Module = hModule;
		//AddHook(hModule);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
//EasyHook入口点
extern "C" __declspec(dllexport) BOOL CALLBACK NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* pInfo)
{
	AddHook(g_Module);
	return TRUE;
}

//添加钩子
void AddHook(HMODULE Module)
{
	std::wstring msg = L"Extension loaded successfully! Please save your file. For more options, press the F1 key.";
	msg += L"\nDebug：\n";
	msg += L"  HWND->";
	GetMainHwnd();

	msg += std::to_wstring((int)g_hwnd).c_str();
	msg += L"\n  ProcessID->";
	msg += std::to_wstring(GetCurrentProcessId());
	MessageBoxW(g_hwnd,msg.c_str(), L"winmoes", MB_OK | MB_ICONINFORMATION);

	G_HOOK = RegisterWindowMessageW(TEXT("SHELLHOOK"));
	bool isHook = RegisterShellHookWindow(g_hwnd);

	lpPrevWndProc = SetWindowLongA(g_hwnd, -4, (LONG)WndProc);
	if (lpPrevWndProc == NULL)
		lpPrevWndProc = SetWindowLongW(g_hwnd, -4, (LONG)WndProc);
}

// 判断进程ID是否存在
BOOL isExistProcess(DWORD process_id)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {

		if (pe.th32ProcessID == process_id)
		{
			return TRUE;
		}
	}
	CloseHandle(hSnapshot);
	return FALSE;
}

DWORD CurProcessID = 0;

//帮助菜单
void OnHelpKey(WPARAM wParm, LPARAM lParam)
{
	//创建进程
	STARTUPINFO stStartUpInfo;
	memset(&stStartUpInfo, 0, sizeof(stStartUpInfo));
	stStartUpInfo.cb = sizeof(stStartUpInfo);

	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	//给设置程序传过去主窗口句柄和进程ID用于关联窗口和关闭进程
	std::wstring cmd = GetExePath() + L"\\MWSettings.dll ";
	cmd += std::to_wstring((int)g_hwnd);
	cmd += L" ";
	cmd += std::to_wstring(GetCurrentProcessId());

	bool ret = ::CreateProcessW(NULL, (LPWSTR)cmd.c_str(), NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &stStartUpInfo, &stProcessInfo);

	CurProcessID = stProcessInfo.dwProcessId;
}

//替换保存窗口的对话框
void MessageBox_()
{
	Sleep(500);
	std::wstring wtext,filepath;
	filepath = GetRegSZ(HKEY_CURRENT_USER, L"Software\\Ave Apps\\Windows Style Builder\\Recent Document List", L"Document1");
	wtext += L"The file is located at: ";
	wtext += filepath;
	wtext += L"\nDo you want to open the location where the file is located?";

	//打开文件所在位置
	if (MessageBoxW(g_hwnd, wtext.c_str(), L"Export successful", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		wtext = L"/select,";
		wtext += filepath;
		ShellExecuteW(0, L"open", L"explorer.exe", wtext.c_str(), L"", SW_SHOW);
	}
}


//SHELLHOOK窗口消息循环
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//处理对话框消息 对话框获取图标会触发
	case WM_GETICON:
		//判断是保存窗口对话框 它会获取大图标
		if (wParam == ICON_BIG) {
			GetHWndsByProcessID(hwndList);
			//进一步判断 遍历对话框控件
			for (size_t i = 0; i < hwndList.size(); i++)
			{
				char temp[300];
				GetWindowTextA(hwndList[i], temp, 301);
				text = temp;
				//确定对话框是这个标题
				if (text == "Windows Style Builder")
				{
					text = "";
					//遍历组件
					EnumChildWindows(hwndList[i], EnumChildProc, (LPARAM)hwndList[i]);
					//找到按钮就关闭窗口并弹出对话框
					if (text.find("Use this theme file"))
					{
						SendMessageA(hwndList[i], WM_CLOSE, 0, 0);
						std::thread td(MessageBox_);
						td.detach();
					}
					goto echos;//跳出所有循环
				}
			}
		echos: break;
		}
		break;
	case WM_HELP:
		if (!isExistProcess(CurProcessID) || CurProcessID == 0)
			OnHelpKey(wParam, lParam);//防止重复打开窗口
		break;
	default:
		break;
	}

	return CallWindowProcA((WNDPROC)lpPrevWndProc, hwnd, uMsg, wParam, lParam);
}
