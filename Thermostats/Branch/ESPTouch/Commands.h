#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
class Commands
{
	String* commands;
	//unsigned current_command;
	unsigned commands_size;

public:

	Commands();
	Commands(String* commandArray, unsigned size);
	~Commands();
	bool Funcion_number_from_command(String receivedCommand, unsigned *index);
	void setCommands(String command);
	void setCommands(String* command, unsigned size);
	String getCommand(unsigned index);

private:

	unsigned getCommands_Size();

	void setCommands_size(unsigned size);
};
#endif // COMMANDS_H
