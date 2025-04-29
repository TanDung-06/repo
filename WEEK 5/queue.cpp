#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct NODE 
{
	int key;
	NODE* p_next;
};

struct Queue 
{
	NODE* head;
	NODE* tail;
};

Queue* initalizeQueue() //Hàm tạo một queue.
{
	return new Queue();   //trả về một queue.
}

void enqueue(Queue*& q, int key)  //Hàm thêm một node có dữ liệu key vào queue.
{
	NODE* a = new NODE{ key,nullptr }; //tạo một con trỏ a kiểu node mang giá trị key.
	if (q == nullptr)  //trường hợp chưa tồn tại một queue.
	{
		q = initalizeQueue();  //tạo một queue.
	}
	if (q->head == nullptr)  //trường hợp queue đã tồn tại nhưng rỗng.
	{
		q->head = a;   //thêm node a vào queue.
		q->tail = a;
	}
	else   //trường hợp queue đã tồn tại nhưng không rỗng.
	{
		q->tail->p_next = a;   //thêm node a vào queue.
		q->tail = a;  //di chuyển con trỏ q->tail đến node a (node vào cuối cùng).
	}
}

int dequeue(Queue*& q)   //Hàm trả về dữ liệu node vào queue đầu tiên và lấy node đó ra khỏi queue.
{
	if (q != nullptr && q->head != nullptr)  //trường hợp tồn tại queue và danh sách không rỗng.
	{
		NODE* a = q->head;  //khởi tạo con trỏ a kiểu node trỏ đến node đầu tiên trong queue.
		if (q->head == q->tail)  //trường hợp queue có duy nhất 1 node.
		{
			q->head = nullptr;  //cho con trỏ q->head và con trỏ q->tail trỏ đến nullptr.
			q->tail = nullptr;
		}
		else  //trường hợp queue có nhiều hơn 1 node.
		{
			q->head = q->head->p_next;   //di chuyển con trỏ q->head đến node tiếp theo.
		}
		return a->key;  //trả về dữ liệu của node mà trước đó con trỏ p->head trỏ đến.
	}
	return -1;  //trả về -1 trong trường hợp không tồn tại queue hay queue rỗng.
}

int size(Queue* q)  //Hàm trả về số lượng node trong queue.
{
	int cnt = 0;  //tạo biến đếm.
	if (q != nullptr && q->head != nullptr)  //trường hợp tồn tại queue và queue không rỗng.
	{
		NODE* a = q->head;  //khởi tạo con trỏ a kiểu node trỏ đến node đầu tiên trong queue.
		while (a != nullptr)  //điều kiện dừng vòng lặp là khi con trỏ a trỏ đến nullptr.
		{
			cnt++;  //tăng giá trị biến đếm.
			a = a->p_next;   //di chuyển con trỏ a đến các node tiếp theo trong queue.
		}
	}
	return cnt;  //trả về số lượng node trong queue.
}

bool isEmpty(Queue* q)  //Hàm kiểm trả xem queue có rỗng không? 
{
	if (size(q) == 0)   //trường hợp queue rỗng.
	{
		return false; //trả về false.
	}
	return true;   //trả về true khi queue không rỗng.
}

void oFile(Queue*& q, ofstream &out) //Hàm in dữ liệu của các node trong queue vô file output.txt.
{
	if (isEmpty(q))   //trường hợp queue không rỗng.
	{
		NODE* a = q->head;  //khởi tạo con trỏ a kiểu node trỏ đến vùng dữ liệu con trỏ q->head trỏ đến.
		while (a != nullptr)  //in dữ liệu các node trong queue ra file output.
		{
			out << a->key << " ";
			a = a->p_next;
		}
		out << endl;
	}
	else  //trường hợp queue q rỗng.
	{
		out << "EMPTY" << endl;
	}
}
int main() {
	Queue* q = initalizeQueue();  //tạo một queue q.
	string x; //khai báo biến kiểu chuỗi.
	int a;    //khai báo biến kiểu số nguyên.

	ifstream in("input1.txt");  //Mở file input1.txt.
	ofstream out("output1.txt"); //Mở file output1.txt.

	if (!in || !out)  //xét xem file có lỗi không.
	{
		cout << "Khong mo duoc file!" << endl;
		return -1;
	}

	while (in >> x)  //đọc dữ liệu từ file input, từng dòng, khi gặp dấu cách thì thực hiện so sánh chuỗi x.
	{
		if (x == "init")  //trường hợp đọc được chuỗi init.
		{
			oFile(q, out);  //in dữ liệu các node trong queue q vào file output.
		}
		else if (x == "enqueue")  //trường hợp đọc được chuỗi enqueue.
		{
			in >> a;  //đọc tiếp dữ liệu số nguyên trên cùng một dòng.
			enqueue(q, a);   //thêm node mới có dữ liệu a vào queue.
			oFile(q, out);  //in dữ liệu các node trong queue q vào file output.
		}
		else if (x == "dequeue")  //trường hợp đọc được chuỗi dequeue. 
		{
			dequeue(q);    //lấy node đầu ra khỏi queue.
			oFile(q, out);  //in dữ liệu các node trong queue q vào file output.
		}
		else   cout << "Du lieu trong file input khong hop le!" << endl;   //trường hợp trên dòng chứa chuỗi không hợp lệ
	}

	in.close();  //đóng file.
	out.close();
	return 0;
}