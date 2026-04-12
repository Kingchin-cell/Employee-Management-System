#pragma once
#include<iostream>
#include<windows.h>
#include"worker.h"
#include<fstream>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define FIRENAME "职工信息.txt"
using namespace std;
class WorkerManager
{public:
	WorkerManager();
	void Show_Menu();//菜单
	void Exitsystem();//退出
	void Add_Person();//添加人
	void Save();//保存文件
	void Init_Person();//初始化数组
	int Get_Num();//更新添加后的人数
	void ShowWorker();//显示人
	int IsExist(int id);//人在吗？
	void DeletePerson();//删除人
	void Mod_Person();//修改人
	void Find_Person();//查找人
	void Sort_Person();//排序
	void Clean_All();//删除文件
	void Update();//更新文件状态
	int m_num;
	Worker** m_array;
	bool m_EmptyFire;//文件在吗？
	~WorkerManager();
};
