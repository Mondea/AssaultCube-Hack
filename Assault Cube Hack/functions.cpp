#include "functions.h"
#include "stdafx.h"
#include "proc.h"
#include<iostream>

void SetAmmo(DWORD procId, uintptr_t moduleBase, HANDLE hProcess)
{

	int ammo;

	std::cout << "How much ammo?" << std::endl;
	std::cin >> ammo;

	// Get ProcID of the target process
	DWORD procId = GetProcId(L"ac_client.exe");

	//Getmodulebaseaddress
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	// Resolve bae address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;
	std::cout << "DynamicPtrBaseAddr =" << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;
	// Resolve our ammo pointer chain
	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddr = FindDMAaddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
	std::cout << "AmmoAddr =" << "0x" << std::hex << ammoAddr << std::endl;
	//Read Ammo value

	int ammoValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "current ammo = " << std::dec << ammoValue << std::endl;

	//Write to it
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &ammo, sizeof(ammo), nullptr);

	// Read out again
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);

	std::cout << "New Ammo = " << std::dec << ammoValue << std::endl;
}