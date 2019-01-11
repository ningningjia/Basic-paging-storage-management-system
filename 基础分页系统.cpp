// 基础分页系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
#define N 100
#include"process.h"
#include"memory.h"
#include"list.h"
#include<fstream>
struct node
{
	char name;
	int num;
	int table[N];
};
class syste {
public:
	void in(char name,int num) {
		pro *new_node = new pro();
		new_node->name = name;
		new_node->page_num = num;
		new_node->set_table(m.assign_mem(*new_node));
		new_node->next = NULL;
		if (list == NULL)
			list = new_node;
		else
		{
			pro *p = list;
			//查找最后一个节点
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = new_node;
		}
	}
	void out(char name) {
		m.p_delete(name);
		pro *p, *q;
		p = list;//查找进程 name ；用p记录
		q = p;
		while (p != NULL)
		{
			if (p->name == name)
				break;
			else
			{
				q = p;
				p = p->next;
			}
		}
		if (p == NULL)
		{
			cout << "此进程不存在!";
		}
		else
		{
			if (p->name == q->name)//要删除的是头结点
			{
				list = p->next;
			}
			else
			{
				q->next = p->next;
			}
		}
	}
	void look(char n) {
		
		pro *p = list;
		while (p != NULL) {
			if (p->get_name() == n) {
				break;
			}
			p = p->next;
		}
		if (p == NULL) {
			cout << "无此进程，请检查输入。" << endl;
		}
		else {
			cout << "进程标识：" << p->get_name() << "进程页面数：" << p->get_size() << "页表：";
			for (int i = 0; i < p->get_size(); i++) {
				cout << *(p->get_table() + i) << "  ";
			}
			cout << endl;
		}
	}
	void write() {
		ofstream OutFile("mem.txt");
		//利用构造函数创建txt文本，并且打开该文本
		for (int i = 0; i < N; i++)
		{
			OutFile << *(m.get_page() + i) << '\n';	//把字符串内容，写入mem.txt文件
		}

		OutFile.close();
	};
	void read() {
		int i = 0;
		int w = 0;
		char x;
		ifstream readFile("mem.txt");
		char p[N] = {};
		char q[N] = {};
		while (!readFile.eof())
		{
			readFile >> x;
			m.set_page(x,i);//这个是把文档里面的数对应在i位置的数值上
			p[w] = x;
			i++;
			w++;
		}
		readFile.close();

		//////////////////////////////////////统计
		int j = 0,v=0;
		for (int i = 0; i < N; i++) {
			if (p[i] != '0') {
				while (p[i] != q[j]) {
					if (j == N-1) {
						q[v] = p[i];
						v++;
						break;
					}
					j++;
				}
				j = 0;
			}
		}
		int gg=0;						//gg是一共有多少个进程
		for (int i = 0; i < N; i++) {
			if (q[i] != NULL) {
				gg++;
			}
		}
		///////////////////////////
		node a;
		a.name = NULL;
		a.num = NULL;
		for (int y = 0; y < gg; y++)
		{
			a.name = q[y];
			int dd = 0;
			while (dd < N)
			{
				if (p[dd] == a.name)
				{
					a.num++;
				}
				dd++;
			}
			int hh = 0;
			for (int k = 0; k < N; k++) {
				if (p[k] == a.name) {
					a.table[hh] = k;
					hh++;
				}
				if (hh == a.num)
				{
					break;
				}
			}
			pro *new_node1 = new pro();
			new_node1->name = a.name;
			new_node1->page_num = a.num;
			new_node1->set_table(a.table);
			new_node1->next = NULL;
			a.name = NULL;
			a.num = NULL;
			//
			int listlong = 0;			//listlong是链表当前结点数
			pro *rbp = list;
			if (list != NULL) {
				listlong = 1;
			while (rbp->next != NULL) {
				listlong++;
				rbp = rbp->next;
			}
		}
			if(listlong<gg)
			//
			{
			if (list == NULL)
				list = new_node1;
			else
			{
				pro *pp = list;
				//查找最后一个节点
				while (pp->next != NULL)
				{
					pp = pp->next;
				}
				pp->next = new_node1;
				}
			}

		}
	}
};
	int main()
	{
		int a[3] = {};
		if (a[1] == NULL) {
			cout << "tee";
		}
		syste h;
		int k;
		while (true) {
			cout << "执行菜单：1.查看内存使用情况。2.查看进程。3.创建进程。4.回收进程。5.内存信息写入磁盘。6从磁盘读取信息至内存。" << endl;
			cin >> k;
			if (k == 1) {
				m.display();
			}
			else if (k == 2) {
				char n;
				cout << "请输入查询的进程标识符：";
				cin >> n;
				h.look(n);
			}
			else if (k == 3) {
				char name;
				int num;
				cout << "请输入进程的名称和所需页面：";
				cin >> name;
				cin >> num;
				h.in(name,num);
			}
			else if (k == 4) {
				char name;
				cout << "请输入要回收的进程的标识符：";
				cin >> name;
				h.out(name);
			}
			else if (k == 5) {
				h.write();
			}
			else if (k == 6) {
				h.read();
			}
			else
			{
				cout << "输入命令有误！"<<endl;
			}
		}

	}
