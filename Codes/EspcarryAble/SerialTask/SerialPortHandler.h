#pragma once
#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <Arduino.h>

#define BAUDRATE 115200
class SerialPortHandler
{
	unsigned stackSize;
	String *stackData;

	void CalculateSize( char* str);
	void startpoints(char* str, unsigned*);
  void ConvertToStack(char*); //string decodeCommand(string, unsigned*); //return data, and return path in paramlist 

public:
	SerialPortHandler();
	~SerialPortHandler();

  bool useStack(String*);
	bool Input(String*,String);
	bool getdata(String*);

	void prints(String);
	void printshelp();//data param)
};

#endif // SERIALPORTHANDLER_H
