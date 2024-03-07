#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

namespace memory
{
	inline HANDLE gHandle;

	inline uintptr_t pID;


	uintptr_t GetProcID(const wchar_t* process);
	uintptr_t GetModuleBaseAddress(uintptr_t procID, const wchar_t* module);
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

	template <typename T> T Read(uintptr_t address)
	{
		T ret;
		ReadProcessMemory(gHandle, (LPCVOID)address, &ret, sizeof(T), nullptr);
		return ret;
	}
	template <typename T> bool Write(uintptr_t address, T value)
	{
		return WriteProcessMemory(gHandle, (LPVOID)address, &value, sizeof(T), nullptr);
	}


}