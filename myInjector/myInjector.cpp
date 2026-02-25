
#include <windows.h>
#include <iostream>


int getPaintPid() {
	HWND hwnd = FindWindowW(L"MSPaintApp", NULL);
	if (hwnd == NULL) {
		std::cout << "couldnt find process" << std::endl;
		return 1;
	}
	std::cout << "found process" << std::endl;

	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	std::cout << "pid: " << pid << std::endl;
	return pid;
}




int main()
{
	const wchar_t* dllPath = L"C:\\Users\\tomer\\source\\repos\\injected\\x64\\Release\\injected.dll";

	//int pid = getPaintPid();
	int pid;
	//inject a certain pid
	std::cout << "enter pid:\n ";
	std::cin >> pid;
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

	//save the dll path into paint's memory
	size_t pathSize = (wcslen(dllPath) + 1) * sizeof(wchar_t);
	LPVOID pTargetMemory = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	WriteProcessMemory(hProcess, pTargetMemory, dllPath, pathSize, NULL);

	HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll"); //kernel32.dll is saved in the same address
	LPTHREAD_START_ROUTINE pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pLoadLibrary, pTargetMemory, 0, NULL);
	if (hThread != NULL) {
		std::cout << "injected!" << std::endl;
		CloseHandle(hThread); 
	}

	CloseHandle(hProcess); 
	return 0;
}

