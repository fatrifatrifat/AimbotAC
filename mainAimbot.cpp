#include "vector.h"
#include "memory.h"
#include "offsets.h"
#include <iostream>

struct Entity
{
	Vec3D headPos;
	DWORD health;
	int team;
};

int main()
{
	uintptr_t procId = memory::GetProcID(L"ac_client.exe");
	uintptr_t gameModule = memory::GetModuleBaseAddress(procId, L"ac_client.exe");
	HANDLE handle = 0;
	handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t localPlayer;

	localPlayer = memory::Read<uintptr_t>(gameModule + 0x10f4f4);

	uintptr_t maxPlayer = gameModule + 0x10f500;
	uintptr_t entList = gameModule + 0x10f4f8;
	uintptr_t currEntAddr;
	
	Entity myEnt;
	Entity currEnt;

	bool leftMouseButtonPressed = false;

	maxPlayer = memory::Read<uintptr_t>(maxPlayer);
	std::cout << "MaxPlayer: " << maxPlayer << std::endl;

	while (true)
	{
		
		leftMouseButtonPressed = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

			if (leftMouseButtonPressed)
			{
				float distance;
				float closestHead = FLT_MAX;
				Vec3D closestHeadVector = { 1,2,3 };

				myEnt.team = memory::Read<int>(localPlayer + ac_offsets::team);
				myEnt.health = memory::Read<DWORD>(localPlayer + ac_offsets::health);
				myEnt.headPos = memory::Read<Vec3D>(localPlayer + ac_offsets::headPosVec);

				for (int i = 1; i < maxPlayer; i++)
				{
					currEntAddr = memory::Read<uintptr_t>(entList);
					currEntAddr = memory::Read<uintptr_t>(currEntAddr + i * 0x4);

					if (currEntAddr == NULL)
						continue;

					currEnt.health = memory::Read<int>(currEntAddr + ac_offsets::health);

					if (currEnt.health <= 0)
						continue;

					currEnt.team = memory::Read<int>(currEntAddr + ac_offsets::team);

					if (currEnt.team == myEnt.team)
						continue;

					currEnt.headPos = memory::Read<Vec3D>(currEntAddr + ac_offsets::headPosVec);

					distance = myEnt.headPos.distanceCalculate(currEnt.headPos);

					if (distance < closestHead)
					{
						closestHead = distance;
						closestHeadVector = currEnt.headPos;
					}
				}

				memory::Write<Vec3D>((localPlayer + ac_offsets::viewAngleVec), myEnt.headPos.relativeAngle(closestHeadVector));

				Sleep(10);
			}

			
	}
	

}