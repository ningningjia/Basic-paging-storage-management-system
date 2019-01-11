#pragma once
class mem {							//内存结构
private:
	char page[N];	//内存物理块
	int free_page;	//空闲块数
public:
	void display();	//显示内存使用情况
	int* assign_mem(pro pro_now);
	void p_delete(char name);
	mem();
	char* get_page();
	void set_page(char t,int i);

};
char* mem::get_page() {
	return page;
}
void mem::set_page(char t,int i) {
	this->page[i] = t;
}
mem m;
void mem::display() {				//显示当前内存页的使用情况
	cout << endl << "当前内存使用情况：";
	for (int i = 0; i < N; i++) {
		if (i % 10 == 0) {
			cout << endl;
		}
		cout << this->page[i] << "   ";
	}
	cout << endl;
}
int* mem::assign_mem(pro pro_now)	//进程分配内存算法
{
	int y[N];
	if (this->free_page > pro_now.get_size()) {
		for (int i = 0; i < pro_now.get_size(); i++) {
			for (int n = 0; n < N; n++) {
				if (page[n] == '0' && this->free_page > pro_now.get_size()) {
					y[i] = n;
					page[n] = pro_now.get_name();
					this->free_page--;
					break;
				}
			}
		}
	}
	else {
		cout << "可用页面不足，无法分配！请先回收进程。" << endl;
	}
	return y;
}
void mem::p_delete(char name) {
	for (int i = 0; i < N; i++) {
		if (this->page[i] == name) {
			this->page[i] = '0';
			this->free_page++;
		}
	}
}
mem::mem() {
	this->free_page = 0;
	for (int i = 0; i < N; i++) {		//初始化内存块使用情况
		this->page[i] = '0';
		this->free_page++;
	}
}
