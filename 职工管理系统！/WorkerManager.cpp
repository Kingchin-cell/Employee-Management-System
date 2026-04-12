#define _CRT_SECURE_NO_WARNINGS
#include"WorkerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
WorkerManager::WorkerManager()
{
    ifstream ifs(FIRENAME);
    //文件不存在
    if (!ifs.is_open())
    {
        //cout << "文件不存在" << endl;//test
        this->m_num = 0;
        m_EmptyFire = true;
        this->m_array = NULL;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    //文件内容为空
    if (ifs.eof())
    {
        //cout << "文件内容为空" << endl;//test
        this->m_num = 0;
        m_EmptyFire = true;
        this->m_array = NULL;
        ifs.close();
        return;
    }
    int num = Get_Num();
    m_num = num;
    m_array = new Worker * [m_num];
    this->m_EmptyFire = false;
    Init_Person();
    
    //可能是更好的写法？

    /*int id;
    string name;
    int DeptID;
    while (ifs >> id >> name >> DeptID)
    {

    }*/
    
}
void WorkerManager::Add_Person()
{
    cout << "请输入添加职工数量" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0) 
    {
        int newSize = this->m_num + addNum;
        Worker** newSpace = new Worker * [newSize];
        if (this->m_array != NULL) 
        {
            for (int i = 0; i < this->m_num; i++)
            {
                newSpace[i] = m_array[i];
            }
        }
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;
            int oldnum = m_num;
            cout << "请输入第" << i + 1 << "个员工编号"<<endl;
            cin >> id;
            //防止编号重复
            int flag = 1;
            while (flag)
            {
                flag = 0;
                for (int j = 0; j < oldnum+i; j++)
                {
                    if (newSpace[j]->m_id == id)
                    {
                        cout << "系统中存在相同编号，请重新输入" << endl;
                        flag = 1;
                        cin >> id;
                        break;
                    }
                }
            }
            cout << "请输入第" << i + 1 << "个员工姓名" << endl;
            cin >> name;
            cout << "请选择该员工岗位" << endl;
            cout << "1、儿子" << endl;
            cout << "2、父亲" << endl;
            cout << "3、爷爷" << endl;
            cin >> dSelect;
            Worker* worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                cout << "添加失败！" << endl;
                system("pause");
                system("cls");
               return;//后期添加功能
                break;
            }
            
            newSpace[oldnum + i] = worker;
            
        }
        delete[] m_array;
        m_num = newSize;
        m_array = newSpace;
        
        Save();
        cout << "添加成功！" << endl;
    }
    else
    {
        cout << "输入有误" << endl;
    }
    system("pause");
    system("cls");
}
void WorkerManager::ShowWorker()
{
    if (m_EmptyFire)
    {
        cout << "文件为空或文件不存在，请按数字1添加职工" << endl;
    }
    else
    {
        for (int i = 0; i < m_num; i++)
        {
            m_array[i]->showInfo();
        }
    }
    
}
void WorkerManager::Init_Person()
{
    ifstream ifs(FIRENAME);
    int id;
    string name;
    int DeptID;
    int index=0;
    while (ifs >> id >> name >> DeptID)
    {
        Worker* worker = NULL;
        switch (DeptID)
        {
        case 1:
            worker = new Employee(id, name, DeptID);
            break;
        case 2:
            worker = new Manager(id, name, DeptID);
            break;
        case 3:
            worker = new Boss(id, name, DeptID);
            break;
        }
        m_array[index] = worker;
        index++;
    }
}
int WorkerManager::Get_Num()
{
    ifstream ifs(FIRENAME);
    int id;
    string name;
    int DeptID;
    int count = 0;
    while (ifs >> id >> name >> DeptID)
    {
        count++;
    }
    ifs.close();
    return count;
}
void WorkerManager:: Save()
{
    
    ofstream ofs(FIRENAME);
    for (int i = 0; i < m_num; i++)
    {
        ofs << m_array[i]->m_id << " ";
        ofs << m_array[i]->m_name << " ";
        ofs << m_array[i]->m_DeptID << endl;
    }
    ofs.close();
    
}
int WorkerManager::IsExist(int id)
{
    for (int i = 0; i < m_num; i++)
    {
        if (m_array[i]->m_id == id)
            return i;
    }
    return -1;
}
void WorkerManager::DeletePerson()
{
    if (m_EmptyFire)
    {
        cout << "文件为空或文件不存在，请按数字1添加职工" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "请输入要删除职工的编号" << endl;
        ShowWorker();
        int id;
        cin >> id;
        int index;
        index=IsExist(id);
        if (index != -1)
        {
            for (int i = index; i < m_num - 1; i++)
            {
                m_array[i] = m_array[i + 1];
            }
            m_num--;
            cout << "删除成功" << endl;
            Save();
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
        system("pause");
        system("cls");
    }
}
void WorkerManager::Mod_Person()
{
    if (m_EmptyFire)
    {
        cout << "文件为空或文件不存在，请按数字1添加职工" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "请输入要修改的员工编号" << endl;
        ShowWorker();
        int id;
        cin >> id;
        int index;
        index=IsExist(id);
        if (index != -1)
        {
            cout << "您要修改的职工是：" << endl;
            m_array[index]->showInfo();
            int id;
            string name;
            int Deptid;
            cout << "请输入新职工号" << endl;
            cin >> id;
            cout << "请输入职工姓名" << endl;
            cin >> name;
            cout << "请选择职工岗位" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> Deptid;
            delete m_array[index];
            Worker* worker = NULL;
            switch (Deptid)
            {
            case 1:
                worker = new Employee(id, name, Deptid);
                break;
            case 2:
                worker = new Manager(id, name, Deptid);
                break;
            case 3:
                worker = new Boss(id, name, Deptid);
                break;
            default:
                cout << "输入有误,已自动为您选择1选项" << endl;
                worker = new Employee(id, name, Deptid);
                break;
            }
            m_array[index] = worker;
            Save();
            cout << "修改成功！" << endl;
        }
        else
        {
            cout << "输入有误" << endl;
        }
        system("pause");
        system("cls");
    }
}
void WorkerManager::Find_Person()
{
    if (m_EmptyFire)
    {
        cout << "文件为空或文件不存在，请按数字1添加职工" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "请选择您的查找方式" << endl;
        cout << "1.按编号" << endl;
        cout << "2.按姓名" << endl;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
        {
            cout << "请输入您要查找的编号" << endl;
            int id;
            cin >> id;
            int index = IsExist(id);
            if (index != -1)
            {
                for (int i = 0; i < m_num; i++)
                {
                    if (m_array[i]->m_id == id)
                    {
                        cout << "查找成功，该职工信息如下:" << endl;
                        m_array[i]->showInfo();
                        break;
                    }
                }
            }
            else
            {
                cout << "查无此人" << endl;
            }
            break;
        }
        case 2:
        {
            cout << "请输入你要查找的姓名" << endl;
            string name;
            cin >> name;
            int flag = 0;
            for (int i = 0; i < m_num; i++)
            {
                if (m_array[i]->m_name == name)
                {
                    cout << "查找成功，信息如下" << endl;
                    flag = 1;
                    m_array[i]->showInfo();
                }
            }
            if (flag == 0)
            {
                cout << "查无此人" << endl;
            }
            break;
        }
        default:
            cout << "没有这种查找方式" << endl;
            break;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::Sort_Person()
{
    if (m_EmptyFire)
    {
        cout << "文件为空或文件不存在，请按数字1添加职工" << endl;
        
    }
    else
    {
        cout << "请选择排序方式" << endl;
        cout << "1.按职工号升序" << endl;
        cout << "2.按职工号降序" << endl;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            for (int i = 0; i < m_num ; i++)
            {
                for (int j = i; j < m_num; j++)
                {
                    if (m_array[i]->m_id > m_array[j]->m_id)
                    {
                        Worker* temp = m_array[i];
                        m_array[i] = m_array[j];
                        m_array[j] = temp;
                    }
                }
            }
            Save();
            cout << "排序成功！" << endl;
            
        }
        else if (select == 2)
        {
            for (int i = 0; i < m_num; i++)
            {
                for (int j = i; j < m_num; j++)
                {
                    if (m_array[i]->m_id < m_array[j]->m_id)
                    {
                        Worker* temp = m_array[i];
                        m_array[i] = m_array[j];
                        m_array[j] = temp;
                    }
                }
            }
            cout << "排序成功！" << endl;
        }
        else
        {
            cout << "没有这种排序方式" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::Clean_All()
{
    cout << "确认清空删除所有数据吗" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
        ofstream ofs(FIRENAME);
        ofs.close();
        if (m_array != NULL)
        {
            for (int i = 0; i < m_num; i++)
            {
                if (m_array[i] != NULL)
                {
                    delete m_array[i];
                }
            }
            m_num = 0;
            delete[] m_array;
            m_array = NULL;
            m_EmptyFire = true;
        }
        cout << "您的文件已经全部删除！" << endl;
    }
    else
    {
        cout << "您的文件安全！" << endl;
    }
    system("pause");
    system("cls");
}
void WorkerManager:: Update()
{
    ifstream ifs(FIRENAME);
    cout << "文件状态已更新,当前状态为：" << endl;
    //文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->m_num = 0;
        m_EmptyFire = true;
        this->m_array = NULL;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    //文件内容为空
    if (ifs.eof())
    {
        cout << "内容为空" << endl;//test
        this->m_num = 0;
        m_EmptyFire = true;
        this->m_array = NULL;
        ifs.close();
        return;
    }
    Save();
    m_EmptyFire = false;
    cout << "文件内容不为空" << endl;
}
WorkerManager::~WorkerManager()
{
    if (m_array != NULL)
    {   
        for (int i = 0; i < m_num; i++)
        {
            delete m_array[i];
        }
        delete[] m_array;
        m_array = NULL;
    }
}
void WorkerManager::Show_Menu()
{
    cout << "**********************************************" << endl;
    cout << "**********  欢迎使用"<<RED<<"职工管理系统"<<RESET<<"！ **********" << endl;
    cout << "**********  本管理系统由"<< "\033[32m" << "柒" << "\033[0m" << "开发  **********" << endl;
    cout << "************  0.退出管理程序  ************" << endl;
    cout << "************  1.增加职工信息  ************" << endl;
    cout << "************  2.显示职工信息  ************" << endl;
    cout << "************  3.删除离职职工  ************" << endl;
    cout << "************  4.修改职工信息  ************" << endl;
    cout << "************  5.查找职工信息  ************" << endl;
    cout << "************  6.按照编号排序  ************" << endl;
    cout << "************  7.清空所有数据  ************" << endl;
    cout << "************  8.更新文件状态  ************" << endl;
    cout << "**********************************************" << endl;
    cout << endl;
}
void WorkerManager::Exitsystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
