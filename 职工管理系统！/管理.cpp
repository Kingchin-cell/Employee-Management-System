#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"WorkerManager.h"
using namespace std;
void test();
int main()
{
	
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "输入编号以执行对应操作" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出管理系统
			wm.Exitsystem();
			break;
		case 1://增加职工信息
			wm.Add_Person();
			break;
		case 2://显示职工信息
			wm.ShowWorker();
			system("pause");
			system("cls");
			break;
		case 3://删除离职职工
			wm.DeletePerson();
			break;
		case 4://修改职工信息
			wm.Mod_Person();
			break;
		case 5://查找职工信息
			wm.Find_Person();
			break;
		case 6://按照编号排序
			wm.Sort_Person();
			break;
		case 7://清空所有数据
			wm.Clean_All();
			break;
		case 8://更新文件
			wm.Update();
			system("pause");
			system("cls");
			break;
		default://用户乱输入
			cout <<RED<< "你踏马乱输入什么玩意，想卡BUG是吧？" <<RESET<< endl;
			system("pause");
			cout <<RED<< "给我重新认真输入！！！" <<RESET<< endl;
			system("pause");
			system("cls");
		}
	}
	
	system("pause");
	return 0;
}