#define _CRT_SECURE_NO_WARNINGS
#include"employee.h"
Employee::Employee(int id, string name, int dId)
{
	m_id = id;
	m_name = name;
	m_DeptID = dId;
}
void Employee::showInfo()
{
	cout << "职工编号:" << this->m_id
		<< "\t职工姓名:" << this->m_name
		<< "\t岗位:" << Employee::getDeptName() << endl;
}
string Employee::getDeptName()
{
	return "儿子";
}