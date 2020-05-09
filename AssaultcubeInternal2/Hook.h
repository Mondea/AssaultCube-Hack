#pragma on
#include <Windows.h>


class Hook {
private:
	uintptr_t* src = nullptr;
	uintptr_t* hookFunc = nullptr;
	uintptr_t* ptrToGatewayPtr = nullptr;
	int len;
	bool enabled = false;
	BYTE originalBytes[32]{0};
	uintptr_t* TrampolineHook(uintptr_t* src, uintptr_t* hookFunc, int len);

public:

	Hook(uintptr_t* src, uintptr_t* hookFunc,uintptr_t* gatewayPtr, int len);
	Hook(LPCSTR exportName, LPCWSTR moduleName, uintptr_t* hookFunc, uintptr_t* gatewayPtr, int len);
	void Enable();
	void Disable();
};

