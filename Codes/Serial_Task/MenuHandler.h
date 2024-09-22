#pragma once
#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include "Commands.h"
#include "Functions.h"
#include <Arduino.h>

 #define ERROR	 0		 
 #define MENU		 1		
 #define FUNC		 2	

 #define BACK		 3
 #define QUIT		 4
 #define HELP		 5

class MenuHandler
{
	Commands *MenuCommands, *FunctionCommands;
	MenuHandler** SideMenu;
	Functions* funcs;// object to handle via function pointer

	unsigned Menus_Elems;
	unsigned Funcs_Elems;

public:
	MenuHandler();
	MenuHandler(String*, unsigned, String*, unsigned);
	~MenuHandler();

	bool menu(String*, MenuHandler *&menu, bool (**func)(void*));

	bool addSideMenus(String CallName, MenuHandler*);
	bool addFunctions(String CallName, bool (*func)(void*));
	String print();
private:

	int decodeCommand(String, int*); //return data, and return path in paramlist // *
};
#endif // MENUHANDLER_H
