#pragma once
#include"stdafx.h"


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


// Menu Class---------------------------------------------------------------------------
class Menu {

private:

	std::vector<Menu> members = {};
	static bool isASubmenuOpen;
	static Menu *currentSubmenuPtr;
	static Menu *baseSubmenuPtr;
	static unsigned int menuCursor;

	bool isToggled = false;
	bool isFeature;
	unsigned int submenuCursor = 0;
	Menu * masterPtr;

	std::string name;
	std::string description;

	

public:

	void addMember(std::string name, std::string description, bool isFeature);
	void removeMember(std::string name);
	void listMembers();
	std::string getName() { return this->name; }
	Menu(std::string name, std::string description, bool isFeature);
	void userInputCheck();
	std::string getIsToggled();
	void CursorUp();
	void CursorDown();
	void CursorOut();
	void Toggle();
};
//End Class----------------------------------------------------------------------------


std::string Menu::getIsToggled()
{
	return (isToggled) ? " [ON] " : " [OFF] ";
}

void Menu::Toggle()
{
	isToggled = !isToggled;
}

void Menu::addMember(std::string name, std::string description, bool isFeature)
{
	Menu temp(name, description, isFeature);
	temp.masterPtr = this;
	members.push_back(temp);

}

void Menu::removeMember(std::string name)
{
	int index = 0;
	for (std::vector<Menu>::iterator i = members.begin(); i != members.end(); i++, index++)
	{
		if (members[index].getName() == name)
		{
			members.erase(i);
		}
	}
}
void Menu::listMembers()
{
	int idx = 0;
		for (std::vector<Menu>::iterator i = currentSubmenuPtr->members.begin(); i != currentSubmenuPtr->members.end(); i++, idx++)
		{
			std::cout << ((idx == submenuCursor) ? "-->  " : "     ") << "   " << currentSubmenuPtr->members[idx].name
				<< " " << currentSubmenuPtr->members[idx].description << currentSubmenuPtr->members[idx].getIsToggled() << std::endl;
		}
}

Menu::Menu(std::string name, std::string description, bool isFeature)
{
	this->name = name;
	this->description = description;
	this->isFeature = isFeature;
}

void Menu::userInputCheck()
{
	SHORT temp;
	//NUMPAD5 Select
	temp = GetAsyncKeyState(VK_NUMPAD5);
	if (!(temp & 1) && (temp & 0xF000))
	{
		if (isFeature) {
			currentSubmenuPtr->Toggle();
		}
		else
		{
			currentSubmenuPtr->members[submenuCursor].Toggle();
		}
	}

	//NUMPAD8 UP
	temp = GetAsyncKeyState(VK_NUMPAD8);
	if (!(temp & 1) && (temp & 0xF000))
	{
		CursorUp();
	}

	//NUMPAD2 DOWN
	temp = GetAsyncKeyState(VK_NUMPAD2);
	if (!(temp & 1) && (temp & 0xF000))
	{
		CursorDown();
	}

	//NUMPAD0 OUT
	temp = GetAsyncKeyState(VK_NUMPAD0);
	if (!(temp & 1) && (temp & 0xF000))
	{
		CursorOut();
	}
}

void Menu::CursorUp()
{
	if (this->submenuCursor != (this->members.size())) {
		currentSubmenuPtr = &members[this->submenuCursor++];
	}
}

void Menu::CursorDown()
{
	if (this->submenuCursor) {
		currentSubmenuPtr = &members[this->submenuCursor--];
	}
}

void Menu::CursorOut()
{
	if (!(this->masterPtr == nullptr))
	{
		currentSubmenuPtr = this->masterPtr;
		currentSubmenuPtr->submenuCursor = 0;
	}
}