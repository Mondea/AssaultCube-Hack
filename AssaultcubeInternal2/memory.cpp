#include "pch.h"
#include "memory.h"

void NopMem(BYTE* src, int len) {
	DWORD Temp;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &Temp);
	for (int i = 0; i < len; i++) {
		*(src + i) = 0x90;
	}
	VirtualProtect(src, len, Temp, &Temp);
}

void SetMem(BYTE* src, int len, BYTE byteArr[]) {
	DWORD Temp;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &Temp);
	for (int i = 0; i < len; i++) {
		*(src + i) = byteArr[i];
	}
	VirtualProtect(src, len, Temp, &Temp);
}

void CpyMem(BYTE* src, int len, BYTE byteArr[]) {
	DWORD Temp;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &Temp);
	for (int i = 0; i < len; i++) {
		byteArr[i] = *(src + i);
	}
	VirtualProtect(src, len, Temp, &Temp);
}