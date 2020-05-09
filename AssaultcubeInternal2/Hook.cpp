#include "pch.h"
#include "Hook.h"
#include "memory.h"

Hook::Hook(uintptr_t* src, uintptr_t* hookFunc, uintptr_t* gatewayPtr, int len) {
	this->src = src;
	this->hookFunc = hookFunc;
	this->ptrToGatewayPtr = gatewayPtr;
	this->len = len;
}

Hook::Hook(LPCSTR exportName, LPCWSTR moduleName, uintptr_t* hookFunc, uintptr_t* gatewayPtr, int len) {
	this->src = (uintptr_t*)GetProcAddress(GetModuleHandle(moduleName), exportName);
	this->hookFunc = hookFunc;
	this->ptrToGatewayPtr = gatewayPtr;
	this->len = len;
}
void Hook::Enable() {
	CpyMem((BYTE*)src, len, originalBytes);
	*ptrToGatewayPtr = (uintptr_t)TrampolineHook(src, hookFunc, len);
	enabled = true;
}
void Hook::Disable() {
	SetMem((BYTE*)src,len,originalBytes);
	enabled = false;
}

uintptr_t* Hook::TrampolineHook(uintptr_t* src, uintptr_t* hookFunc, int len) {
	if (len < 5) { return false; }
	uintptr_t* gateway = (uintptr_t*)VirtualAlloc(NULL, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(gateway, len, src, len);
	NopMem((BYTE*)src, 5);

	DWORD temp;
	VirtualProtect(src,len, PAGE_EXECUTE_READWRITE, &temp);
	*(src) = 0xE9;
	*(src + 1) = (uintptr_t)((BYTE*)hookFunc - (BYTE*)src - 5);
	VirtualProtect(src, len, temp, &temp);

	*(gateway + len) = 0xE9;
	*(gateway + len + 1) = (uintptr_t)((BYTE*)src-(BYTE*)gateway-5);

	return gateway;
}