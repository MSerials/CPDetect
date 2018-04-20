#pragma once

#include <string>

#ifndef _ASSEMBLE__
#define _ASSEMBLE__

class IF
{
public:
	IF() {};
	virtual ~IF() {};
	virtual std::string name() = 0;
};

#endif




#ifndef __ASSEMBLYS__
#define __ASSEMBLYS__

class add :public IF
{

	add() {};
};

#endif