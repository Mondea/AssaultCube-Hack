// Assault Cube Hack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
//#include <algorithm>
#include "functions.h"
#include <stdlib.h>
#include <iomanip>

#include "proc.h"
#include "menu.h"

/*
VK_NUMPAD0 0x60 Numeric keypad 0 key
VK_NUMPAD1 0x61 Numeric keypad 1 key
VK_NUMPAD2 0x62 Numeric keypad 2 key
VK_NUMPAD3 0x63 Numeric keypad 3 key
VK_NUMPAD4 0x64 Numeric keypad 4 key
VK_NUMPAD5 0x65 Numeric keypad 5 key
VK_NUMPAD6 0x66 Numeric keypad 6 key
VK_NUMPAD7 0x67 Numeric keypad 7 key
VK_NUMPAD8 0x68 Numeric keypad 8 key
VK_NUMPAD9 0x69 Numeric keypad 9 key
*/


int main()
{
	std::vector<int> keys = { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69 };
	
	Menu Aimbot("Aimbot", "WIP ", true);
	Menu ESP("ESP", "WIP", true);
	Menu setValue("Change stats/items", "",false);
	setValue.addMember("Change Ammo", "", true);

	

	SHORT keyPress;
	do
	{
	

		system("CLS");

		std::cout << "----------------------------------------" << std::endl;
		std::cout << "          Assault Cube Trainer          " << std::endl;
		std::cout << "              -by Davis-                " << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "[_______________M_E_N_U________________]" << std::endl;



		std::cout << "\n Press NUMPAD0 to exit the cheat" << std::endl;
		

		Sleep(100);
	} while (!(GetKeyState(VK_DECIMAL) & 0x8000));

	std::cout << "\n Exiting the cheat" << std::endl;
	Sleep(1000);
    return 0;
}

