#include "Commands.h"

Commands::Commands(){
	commands = nullptr;
	setCommands_size(0);
}

Commands::Commands(String* commandArray, unsigned size){
	setCommands_size(size);
	commands = new String[size];
	for (unsigned i = 0; i < size; i++){
		commands[i] = commandArray[i];
	}
}

Commands::~Commands(){
		delete[] commands;
		commands = nullptr;
}
//Compare input to array elements, then return index of the matched elem. if there is no match then return -1
bool Commands::Funcion_number_from_command(String const receivedCommand, unsigned *index){
	for (unsigned i = 0; i < getCommands_Size(); i++)
	{
		if (receivedCommand==getCommand(i))
		{
			*index = i;
			return true;
		}
	}
	*index = -1;
	return false;//throw unhandled expression
}
// Check for white caraters, if these comming then return
//create a new array with a bigger storege, copy every elems to it, then add the new one to the end of the array
// before point to the new elems array, should delete the old elems array.
void Commands::setCommands(String command){
	if (command == "" || command == " " || command == "\n" || command == "\t"){
		return;
	}
	setCommands_size(getCommands_Size() + 1);
	String* str = new String[getCommands_Size()];
	for (unsigned i = 0; i < getCommands_Size() - 1; i++){
		str[i] = getCommand(i);
	}
	delete[] commands;
	str[getCommands_Size() - 1] = command;
	commands = str;
}

void Commands::setCommands(String* command, unsigned size){
	if(command!=nullptr){
		return;
	}
	commands = new String[size];
	for (unsigned i = 0; i < size; i++) {
		commands[i] = command[i];
	}
}

unsigned Commands::getCommands_Size(){
	return commands_size;
}


String Commands::getCommand(unsigned index){
	if (index < getCommands_Size()){
		return commands[index];
	}
	return "";
}

void Commands::setCommands_size(unsigned size){
	commands_size = size;
}