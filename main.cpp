#include<iostream>
#include <windows.h>
using namespace std;

int main() {
	//1.������Ϸ���ڵľ��
	HWND gameHandle = FindWindow(L"MainWindow", L"ֲ���ս��ʬ���İ�");
	if (gameHandle == NULL) {
		cout << "��Ϸû�д򿪣���ȡ���ھ��ʧ��" << endl;
		return 0;
	}

	//2.���ݴ��ھ����ȡ����ID
	DWORD dwPID = 0;
	GetWindowThreadProcessId(gameHandle, &dwPID);
	if (dwPID == 0) {
		cout << "��ȡ��Ϸ����PIDʧ��" << endl;
		return 0;
	}

	//3.���ݽ���ID��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID); 
	if (hProcess == nullptr) {
		cout << "��ȡ��Ϸ���̾��ʧ��" << endl;
		return 0;
	}

	//4.��ȡ��Ϸ�����ڴ�
	DWORD SunBaseAddress = 0x006A9EC0;     //Ҫ��ȡ�ĵ�ַ
	DWORD SunBaseAddressValue = 0;         //��ȡ��ŵ�ֵ
	DWORD Size = 0;                       //ʵ�ʶ�ȡ�����ֽڴ�С
	if (ReadProcessMemory(hProcess, (void*)SunBaseAddress, &SunBaseAddressValue, sizeof(DWORD), (SIZE_T*)&Size) == 0) {
		cout << "��ȡ����ַʧ��" << GetLastError() << endl;
		return 0;
	}
	DWORD SunOffsetFirst = 0x768;     //һ��ƫ����
	DWORD SunOffsetFirstValue = 0;         //һ��ƫ�����д�ŵ�ֵ
	DWORD Size1 = 0;
	if (ReadProcessMemory(hProcess, (void*)(SunBaseAddressValue + SunOffsetFirst), &SunOffsetFirstValue, sizeof(DWORD), (SIZE_T*)&Size1) == 0) {
		cout << "��ȡһ��ƫ�Ƶ�ַʧ��" << GetLastError() << endl;
		return 0;
	}
	DWORD SunOffsetSecond = 0x5560;     //һ��ƫ����
	DWORD SunValue = 0;         //һ��ƫ�����д�ŵ�ֵ:����ֵ
	DWORD Size2 = 0;
	if (ReadProcessMemory(hProcess, (void*)(SunOffsetFirstValue + SunOffsetSecond), &SunValue, sizeof(DWORD), (SIZE_T*)&Size2) == 0) {
		cout << "��ȡ�����ַʧ��" << GetLastError() << endl;
		return 0;
	}
	cout << "���ڵ������ǣ�" << SunValue << endl;

	return 0;
}