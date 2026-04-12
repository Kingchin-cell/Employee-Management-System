#pragma once
#include"worker.h"
class Manager :public Worker
{public:
	Manager(int id, string name, int dID);
	void showInfo();
	string getDeptName();
};

