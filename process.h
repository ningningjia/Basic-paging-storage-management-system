#pragma once
class pro {							//进程结构
private:
	char name;	//进程名
	int page_num;		//进程所需页数
	int table[N];		//进程页表
	pro *next;
public:
	friend class syste;
	int* get_table() {
		return this->table;
	}
	int get_size() {
		return this->page_num;
	}
	char get_name() {
		return this->name;
	}
	void set_name(char name) {
		this->name = name;
	}
	void set_num(int num) {
		this->page_num = num;
	}
	void set_table(int* p) {
		for (int i = 0; i < this->page_num; i++) {
			this->table[i] = *(p + i);
		}
	}
};