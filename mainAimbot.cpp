#include "vector.h"
#include "memory.h"
#include "offsets.h"
#include <iostream>

struct Entity
{
	Vec3D headPos;
	int health;
	int team;
};

int main()
{
	uintptr_t procId = memory::GetProcID(L"ac_client.exe");
	uintptr_t gameModule = memory::GetModuleBaseAddress(procId, L"ac_client.exe");
	HANDLE handle = 0;
	handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t localPlayer;

	do {
		localPlayer = gameModule + 0x10f4f4;
	} while (localPlayer == NULL);

	uintptr_t maxPlayer = gameModule + 0x10f500;
	uintptr_t entList = gameModule + 0x10f4f8;
	uintptr_t currEntAddr;
	Entity myEnt;
	Entity currEnt;
	

	
		myEnt.team = memory::Read<int>(localPlayer + ac_offsets::team);

		maxPlayer = memory::Read<uintptr_t>(maxPlayer);

		std::cout << maxPlayer << std::endl;
		for (int i = 1; i <= maxPlayer; i++)
		{
			currEntAddr = memory::Read<uintptr_t>(entList + i * 0x4);

			if (currEntAddr == NULL)
				continue;

			currEnt.health = memory::Read<int>(currEntAddr + ac_offsets::health);

			if (currEnt.health >= 0)
				continue;

			currEnt.team = memory::Read<int>(currEntAddr + ac_offsets::team);

			if (currEnt.team == myEnt.team)
				continue;

			std::cout << "Lol" << std::endl;
			std::cout << currEnt.health << std::endl;
			
		}

	
	

}