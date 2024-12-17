#include<iostream>
#include <windows.h>
using namespace std;

int main() {
	//1.查找游戏窗口的句柄
	HWND gameHandle = FindWindow(L"MainWindow", L"植物大战僵尸中文版");
	if (gameHandle == NULL) {
		cout << "游戏没有打开，获取窗口句柄失败" << endl;
		return 0;
	}

	//2.根据窗口句柄获取进程ID
	DWORD dwPID = 0;
	GetWindowThreadProcessId(gameHandle, &dwPID);
	if (dwPID == 0) {
		cout << "获取游戏窗口PID失败" << endl;
		return 0;
	}

	//3.根据进程ID获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID); 
	if (hProcess == nullptr) {
		cout << "获取游戏进程句柄失败" << endl;
		return 0;
	}

	//4.读取游戏进程内存
	DWORD SunBaseAddress = 0x006A9EC0;     //要读取的地址
	DWORD SunBaseAddressValue = 0;         //读取存放的值
	DWORD Size = 0;                       //实际读取到的字节大小
	if (ReadProcessMemory(hProcess, (void*)SunBaseAddress, &SunBaseAddressValue, sizeof(DWORD), (SIZE_T*)&Size) == 0) {
		cout << "读取基地址失败" << GetLastError() << endl;
		return 0;
	}
	DWORD SunOffsetFirst = 0x768;     //一级偏移量
	DWORD SunOffsetFirstValue = 0;         //一级偏移量中存放的值
	DWORD Size1 = 0;
	if (ReadProcessMemory(hProcess, (void*)(SunBaseAddressValue + SunOffsetFirst), &SunOffsetFirstValue, sizeof(DWORD), (SIZE_T*)&Size1) == 0) {
		cout << "读取一级偏移地址失败" << GetLastError() << endl;
		return 0;
	}
	DWORD SunOffsetSecond = 0x5560;     //一级偏移量
	DWORD SunValue = 0;         //一级偏移量中存放的值:阳光值
	DWORD Size2 = 0;
	if (ReadProcessMemory(hProcess, (void*)(SunOffsetFirstValue + SunOffsetSecond), &SunValue, sizeof(DWORD), (SIZE_T*)&Size2) == 0) {
		cout << "读取阳光地址失败" << GetLastError() << endl;
		return 0;
	}
	cout << "现在的阳光是：" << SunValue << endl;

	return 0;
}