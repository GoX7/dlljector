#include "init.h"

int getArg(int argc, char* argv[], int* dwPid, char*& cDll)
{
	if (argc < 3)
	{
		std::cerr << "Usage: inject.exe [pid] [dll path]" << std::endl;
		return -1;
	}
	else
	{
		*dwPid = atoi(argv[1]);
		cDll = argv[2];
		return 1;
	}
}

int openProcess(int dwPid, HANDLE* hProcess)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPid);
	if (hProc == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Error: Open Process" << std::endl;
		return -1;
	}
	else {
		std::cout << "Success: Open Process" << std::endl;
		*hProcess = hProc;
		return 1;
	}
}

int injectDll(int dwPid, char* dll, HANDLE hProcess, HANDLE* hTheard)
{
	size_t buffer = strlen(dll)+1;
	LPVOID lpMemory = VirtualAllocEx(hProcess, NULL, buffer, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
	if (!lpMemory)
	{
		std::cerr << "Error: Virtual Alloc" << std::endl;
		return -1;
	}
	

	if (!WriteProcessMemory(hProcess, lpMemory, (LPVOID)dll, buffer, NULL))
	{
		std::cerr << "Error: Write Process" << std::endl;
		return -1;
	}

	LPVOID kernel32 = (LPVOID)GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryA");
	HANDLE theard = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)kernel32, lpMemory, 0, NULL);
	if (theard == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Error: Create Theard" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Success: Create Theard" << std::endl;
		*hTheard = theard;
		return 1;
	}
}

int main(int argc, char* argv[])
{ 
	HANDLE hProcess;
	HANDLE hTheard;
	char* cDll = new char(255);
	int dwPid;

	if (getArg(argc, argv, &dwPid, cDll) < 1) return 1;
	if (openProcess(dwPid, &hProcess) < 1) return 1;
	if (injectDll(dwPid, cDll, hProcess, &hTheard) < 1) return 1;
	
	std::cout << "Success: Inject DLL" << std::endl;
	std::cout << "Worked..." << std::endl;

	WaitForSingleObject(hTheard, INFINITE);
	CloseHandle(hTheard);
	CloseHandle(hProcess);
	return 1;
}