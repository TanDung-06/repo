#include<iostream>
#include<fstream>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data)  //Hàm tạo một node mới với key=data.
{
	return new NODE{ data,nullptr,nullptr,1 };
}

void Insert(NODE*& pRoot, int x)
{

}

void remove(NODE*& pRoot, int x)
{

}

bool isAVL(NODE* pRoot)
{

}