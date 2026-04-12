#define _CRT_SECURE_NO_WARNINGS
#include"boss.h"
Boss::Boss(int id, string name, int dId)
{
	m_id = id;
	m_name = name;
	m_DeptID = dId;
}
void Boss::showInfo()
{
	cout << "职工编号:" << this->m_id
		<< "\t职工姓名:" << this->m_name
		<< "\t岗位:" << Boss::getDeptName() << endl;
}
string Boss::getDeptName()
{
	return "爷爷";
}