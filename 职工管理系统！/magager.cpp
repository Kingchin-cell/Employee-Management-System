#define _CRT_SECURE_NO_WARNINGS
#include"manager.h"
Manager::Manager(int id, string name, int dId)
{
	m_id = id;
	m_name = name;
	m_DeptID = dId;
}
void Manager::showInfo()
{
	cout << "职工编号:" << this->m_id
		<< "\t职工姓名:" << this->m_name
		<< "\t岗位:" << Manager::getDeptName() << endl;
}
string Manager::getDeptName()
{
	return "爸爸";
}