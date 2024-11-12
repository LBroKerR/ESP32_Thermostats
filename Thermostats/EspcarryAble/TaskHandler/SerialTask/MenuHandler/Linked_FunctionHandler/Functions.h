#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions
{
	bool (*functions)(void*);

public:
	// storing a function location!
	Functions(bool (*function)(void*)) : functions(function) {}
	Functions() :functions(nullptr) {}
	~Functions() {}

	// return the stored function!
	bool (*getFunc())(void*) {
		return functions;
	}
	//save the function
	void setFunc(bool (*function)(void*)) {
		functions = function;
	}
};
#endif // FUNCTIONS_H
