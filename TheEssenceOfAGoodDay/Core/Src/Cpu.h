#pragma once
#include "corestd.h"

class Cpu
{
	ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	int32          numProcessors;
	Handle         self;

public:

	void   Initialize_CPU();
	double Get_CPU();
};