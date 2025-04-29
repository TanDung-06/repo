#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct NODE
{
	int key;
	NODE* p_next;
};

struct Stack
{
	NODE* top;
};

Stack* initalizeStack()      //Hàm tạo một Stack.
{
	return new Stack();   //trả về một stack.
}

void push(Stack*& s, int key)  //Hàm thêm một node có dữ liệu key vào đỉnh stack.
{
	if (s == nullptr) //trường hợp chưa tồn tại một stack.
	{
		s = initalizeStack();   //tạo một stack.
	}
	NODE* a = new NODE{ key,nullptr };   //tạo một con trỏ a kiểu node mang giá trị key.
	a->p_next = s->top;  //cho con trỏ a->p_next trỏ đến node ở đỉnh stack.
	s->top = a; //vì sau bước trên thì node ở đỉnh stack là a nên cho con trỏ top trỏ đến node a.
}

int pop(Stack*& s)   //Hàm trả về dữ liệu node đỉnh stack và lấy node đó ra khỏi stack.
{
	if (s != nullptr && s->top != nullptr)   //chỉ thực hiện khi tồn tại stack và có ít nhất một node trong stack.
	{
		NODE* a = s->top;   //Khởi tạo con trỏ a kiểu node trỏ đến node ở đỉnh stack.
		s->top = s->top->p_next;  //nếu còn node dưới node đỉnh thì dời con trỏ top xuống node đó, còn không thì trỏ đến nullptr và node đỉnh ban đầu không còn trong stack nữa.
		return a->key;  //trả về dữ liệu của con trỏ đỉnh ban đầu.
	}
	return -1;  //còn các trường hợp khác thì trả về -1.
}

int size(Stack * s)  //Hàm trả về số lượng node trong stack.
{
	int cnt = 0;  //tạo biến đếm.
	if (s == nullptr)   //trường hợp không tồn tại stack.
	{
		return cnt;   //trả về cnt.
	}
	else  //trường hợp tồn tại stack.
	{
		NODE* a = s->top;  //khởi tạo con trỏ a kiểu node trỏ đến node ở đỉnh stack.
		while (a != nullptr)  //điều kiện dừng vòng lặp là khi con trỏ a trỏ đến nullptr.
		{
			cnt++;  //tăng giá trị biến đếm.
			a = a->p_next;  //di chuyển con trỏ a đến các node tiếp theo trong stack.
		}
		return cnt;  //trả về số lượng node trong stack.
	}
}

bool isEmpty(Stack* s)  //Hàm kiểm trả xem stack có rỗng không? 
{
	if (size(s) == 0)  //trường hợp stack rỗng.
	{  
		return false;  //trả về false.
	}
	return true;  //trả về true khi stack không rỗng.
}

void oFile(Stack* s ,ofstream &out)  //Hàm in dữ liệu của các node trong stack vô file output.txt.
{
	if (isEmpty(s))   //trường hợp stack không rỗng.
	{
		Stack* dao = initalizeStack();  //tạo một stack mới.
		NODE* a = s->top;  //khởi tạo con trỏ a kiểu node trỏ đến vùng dữ liệu con trỏ s->top trỏ đến.
		while (a != nullptr)  //tạo ra một stack ngược so với stack ban đầu.
		{
			push(dao, a->key);  //thêm node mới.
			a = a->p_next;  //di chuyển con trỏ a đến các node tiếp theo trong stack s.
		}
		a = dao->top;  //trỏ con trỏ a đến node ở đỉnh của stack dao.
		while (a != nullptr)   //in dữ liệu các node trong stack dao ra file output.
		{
			out<< a->key << " ";
			a = a->p_next;
		}
	    out << endl;   
	}
	else  //trường hợp stack s rỗng.
	{
		out << "EMPTY" << endl;
	}
}

int main() {
	Stack* s = initalizeStack();   //tạo một stack s.
	string x;  //khai báo biến kiểu chuỗi.
	int a;  //khai báo biến kiểu số nguyên.

	ifstream infile("input.txt");  //Mở file input.txt.
	ofstream outfile("output.txt"); //Mở file output.txt.

	if (!infile || !outfile)   //xét xem file có lỗi không.
	{
		cout << "Loi mo file input.txt" << endl;
		return -1;
	}
	
	while (infile >> x)  //đọc dữ liệu từ file input, từng dòng, khi gặp dấu cách thì thực hiện so sánh chuỗi x.
	{
		if (x == "init")  //trường hợp đọc được chuỗi init.
		{
			oFile(s,outfile);  //in dữ liệu các node trong stack s vào file output.
		}
		else if (x == "push")  //trường hợp đọc được chuỗi push.
		{
			infile >> a;  //đọc tiếp dữ liệu số nguyên trên cùng một dòng.
			push(s, a);   //thêm node mới có dữ liệu a vào đỉnh stack.
			oFile(s, outfile);  //in dữ liệu các node trong stack s vào file output
		} 
		else if (x == "pop")  //trường hợp đọc được chuỗi pop. 
		{
			pop(s);  //lấy node ở đỉnh stack ra khỏi stack.
			oFile(s, outfile);  //in dữ liệu các node trong stack s vào file output
		}
		else cout << "Du lieu trong file khong hop le!";   //trường hợp trên dòng chứa chuỗi không hợp lệ
	}

	infile.close();     //đóng file.
	outfile.close();
	return 0;
}
