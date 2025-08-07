#include <iostream>
#include <windows.h>

int getArg(int argc, char* argv[], int* dwPid, char*& cDll);
int openProcess(int dwPid, HANDLE* hProcess);
int injectDll(int dwPid, char* dll, HANDLE hProcess, HANDLE* hTheard, LPVOID* lpMemory);
int waitDll(HANDLE hProcess, HANDLE hTheard, LPVOID lpMemory);